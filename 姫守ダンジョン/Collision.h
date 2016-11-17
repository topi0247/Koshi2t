//
//	@file	Collision.h
//	@brief	Ç†ÇΩÇËîªíËä«óùÉNÉâÉX
//	@date	2016/11/14
//	@outherÅ@ãgâzëÂãR

#pragma once
#include "./Mesh/CD3DXMESH_ANIM.h"
#include "Origin.h"
#define RAY_DISTANCE 3

class Collision
{
public:
	~Collision();
	Collision();
	bool RayIntersect(CD3DXMESH_ANIM* pMeshA, CD3DXMESH_ANIM* pMeshB,float* pfDistance, D3DXVECTOR3* pvNormal/*,float* pfDistance*/);
	D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);
	HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices);
};

