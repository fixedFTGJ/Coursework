#include "StdAfx.h"
#include "Mesh.h"
#include "Utils.h"
#include "Graphics.h"

#include <sstream>
#include <boost/shared_ptr.hpp>

using namespace boost;
using namespace std;


CSubMesh::CSubMesh( DWORD iMatID)
: dwMatID(iMatID),
m_curr_start_index(0)
{
}

CSubMesh::~CSubMesh( void )
{
}

bool CSubMesh::Load( std::istream& in )
{
	// это дефайн что бы было проще писать в файл
#define _read(data) in.read((char*)&data, sizeof(data))

	WORD iVertCount;
	DWORD iIdxCount;
	_read(dwMatID);
	_read(iVertCount);
	_read(iIdxCount);

	m_vertices.resize(iVertCount);
	m_indices.resize(iIdxCount);

	in.read((char*)&m_vertices[0], iVertCount*sizeof(MyVertex));
	in.read((char*)&m_indices[0], iIdxCount*sizeof(WORD));

	return true;
}

size_t CSubMesh::GetVertsCount()
{
	return m_vertices.size();
}

size_t CSubMesh::GetIdxCount()
{
	return m_indices.size();
}

void CSubMesh::SetStartIndex( WORD index )
{
	int delta = int(index) - int(m_curr_start_index);
	m_curr_start_index = index;
	for(size_t i=0; i<m_indices.size(); i++)
		m_indices[i] = WORD(int(m_indices[i])+delta);
}

CMesh::CMesh(void)
: m_pVB(NULL),
m_pIB(NULL)
{
}

CMesh::~CMesh(void)
{
	Release();
}

bool CMesh::Load( const std::string& strFileName )
{
	std::string contents = GetFileAsString(strFileName);
	if (contents.length()==0)
		return false;

	// поток ввода из "файла"
	std::stringstream in(contents);

	MeshHeader meshHeader;
	int iTotalVerts = 0;
	int iTotalIdx = 0;
	unsigned int subMeshesCount = 0;

	in.read((char*)&meshHeader, sizeof(MeshHeader));
	in.read((char*)&subMeshesCount, sizeof(unsigned int));

	m_vecSubMeshes.resize(subMeshesCount);
	for (unsigned int i=0; i<subMeshesCount; i++)
	{
		m_vecSubMeshes[i].Load(in);
		iTotalVerts += m_vecSubMeshes[i].GetVertsCount();
		iTotalIdx += m_vecSubMeshes[i].GetIdxCount();
	}

	// создаём Vertex Buffer
	m_pVB = Graphics::get().CreateVertexBuffer(iTotalVerts*sizeof(MyVertex), D3DUSAGE_WRITEONLY, D3DPOOL_MANAGED);
	if (m_pVB==NULL) // если ошибка
		return false;

	// создаём Index Buffer
	m_pIB = Graphics::get().CreateIndexBuffer(iTotalIdx*sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED);
	if (m_pIB==NULL) // если ошибка
	{
		Release();
		return false;
	}

	void* pData;
	if (FAILED(m_pVB->Lock(0, 0, &pData, 0)))
	{
		Release();
		return false;
	}
	int offset = 0;
	char* pChData=(char*)pData;
	for (unsigned int i=0; i<subMeshesCount; i++)
	{
		size_t len = m_vecSubMeshes[i].GetVertsCount()*sizeof(MyVertex);
		memcpy(pChData, &m_vecSubMeshes[i].GetVerts()[0], len);

		m_vecSubMeshes[i].SetStartIndex(offset);
		offset += m_vecSubMeshes[i].GetVertsCount();

		pChData += len;
	}
	m_pVB->Unlock();

	if (FAILED(m_pIB->Lock(0, 0, &pData, 0)))
	{
		Release();
		return false;
	}
	pChData=(char*)pData;
	for (unsigned int i=0; i<subMeshesCount; i++)
	{
		size_t len = m_vecSubMeshes[i].GetIdxCount()*sizeof(WORD);
		memcpy(pChData, &m_vecSubMeshes[i].GetIdx()[0], len);
		pChData += len;
	}
	m_pIB->Unlock();

	return true;
}

void CMesh::Release()
{
	if (m_pVB)
	{
		Graphics::get().Release(m_pVB);
		m_pVB = NULL; 
	}
	if (m_pIB)
	{
		Graphics::get().Release(m_pIB);
		m_pIB = NULL;
	}
}

HRESULT CMesh::Draw( LPDIRECT3DDEVICE9 pd3dDevice)
{
	int startIndex=0;
	for (size_t i=0; i<m_vecSubMeshes.size(); i++)
	{
		HRESULT hr = pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, m_vecSubMeshes[i].GetStartIndex(), m_vecSubMeshes[i].GetVertsCount(), startIndex, m_vecSubMeshes[i].GetIdxCount()/3);
		startIndex += m_vecSubMeshes[i].GetIdxCount();
	}
	return D3D_OK;
}
