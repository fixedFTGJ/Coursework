#include "stdafx.h"
#include "VertexTypes.h"

/*
D3DVERTEXELEMENT9 dwDeclVertPosNormalTc[] = 
{
	{0, 0,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, 
	D3DDECLUSAGE_POSITION, 0},
	{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, 
	D3DDECLUSAGE_NORMAL, 0},
	{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, 
	D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
};
*/

D3DVERTEXELEMENT9 dwDeclMyVertex[] = 
{
	{0, 0,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, 
	D3DDECLUSAGE_POSITION, 0},
	
/*	{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, 
	D3DDECLUSAGE_NORMAL, 0},
	{0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, 
	D3DDECLUSAGE_NORMAL, 1},
	{0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, 
	D3DDECLUSAGE_NORMAL, 2},
*/	
	{0, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, 
	D3DDECLUSAGE_TEXCOORD, 0},
	
	{0, 64, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, 
	D3DDECLUSAGE_COLOR, 0},
	
	D3DDECL_END()
};
int operator==(const VertPosNormalTc& a,const VertPosNormalTc& b)
{
	return (a.m_pos==b.m_pos) && (a.m_normal==b.m_normal) && (a.m_tc==b.m_tc);
}

int operator==( const MyVertex& a,const MyVertex& b )
{
	return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) &&
		(a.tx == b.tx) && (a.ty == b.ty) && (a.tz == b.tz) &&
		(a.bx == b.bx) && (a.by == b.by) && (a.tz == b.tz) &&
		(a.nx == b.nx) && (a.ny == b.by) && (a.nz == b.nz) &&
		(a.tu1 == b.tu1) && (a.tv1 == b.tv1) &&
		(a.tu2 == b.tu2) && (a.tv2 == b.tv2) &&
		(a.color == b.color);
}
