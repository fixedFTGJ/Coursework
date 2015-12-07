#pragma once
#include <d3dx9.h>

struct VertPosDiffuse 
{
	D3DXVECTOR3 m_pos;
	D3DCOLOR m_color;
	VertPosDiffuse(D3DXVECTOR3 pos, D3DCOLOR color)
		: m_pos(pos), m_color(color)
	{}
};

struct VertPosTc 
{
	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_tc;
	VertPosTc() {}
	VertPosTc(D3DXVECTOR3 pos, D3DXVECTOR2 tc)
		: m_pos(pos), m_tc(tc)
	{}
};

struct VertPosNormalTc
{
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_normal;
	D3DXVECTOR2 m_tc;
	VertPosNormalTc() {}
	VertPosNormalTc(D3DXVECTOR3 pos, D3DXVECTOR3 nrm, D3DXVECTOR2 tc)
		: m_pos(pos), m_normal(nrm), m_tc(tc)
	{}
};

// выравнивание = 1 что бы данные шли последовательно
#pragma pack(1)
// структура для хранения вертекса
struct MyVertex
{
	float x, y, z; // pos
	float tx, ty, tz; // tangent
	float bx, by, bz; // binormal
	float nx, ny, nz; // normal
	float tu1, tv1, tu2, tv2; // texcoords
	DWORD color; // vertex color
};
#pragma pack()

int operator==(const VertPosNormalTc& a,const VertPosNormalTc& b);
int operator==(const MyVertex& a,const MyVertex& b);

//D3DVERTEXELEMENT9 dwDeclVertPosNormalTc[];
D3DVERTEXELEMENT9 dwDeclMyVertex[];