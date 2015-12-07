#pragma once

#include <vector>
#include <string>
#include "VertexTypes.h"

class Graphics;

struct MeshHeader
{
	DWORD flags[16];
};

class CSubMesh
{
	WORD m_curr_start_index;
	//! ������������� ��������� ������� �������
	DWORD dwMatID;
	//! �������� �������
	std::vector<MyVertex> m_vertices;
	//! ������� (��� ������ ������) �������
	std::vector<WORD> m_indices;

protected:
	friend class CMesh;
	void SetStartIndex(WORD index);

public:
	CSubMesh(DWORD iMatID = 0);
	~CSubMesh(void);
	//! �������� ������� �� ������
	bool Load(std::istream& in);

	size_t GetVertsCount();
	size_t GetIdxCount();

	std::vector<MyVertex>& GetVerts() { return m_vertices; }
	std::vector<WORD>& GetIdx() { return m_indices; }

	WORD GetStartIndex() { return m_curr_start_index; }
};

class CMesh
{
	std::vector<CSubMesh> m_vecSubMeshes;

	// index buffer
	LPDIRECT3DINDEXBUFFER9 m_pIB;
	// vertex buffer
	LPDIRECT3DVERTEXBUFFER9 m_pVB;

	void Release();

protected:
	friend class Graphics;
	LPDIRECT3DINDEXBUFFER9 GetIB() { return m_pIB; }
	LPDIRECT3DVERTEXBUFFER9 GetVB() { return m_pVB; }
	CMesh(void);
	virtual ~CMesh(void);
	virtual bool Load(const std::string& strFileName);

public:
	HRESULT Draw(LPDIRECT3DDEVICE9 pd3dDevice);
};

typedef CMesh* CMeshPtr; // ��� ���������� �� ���