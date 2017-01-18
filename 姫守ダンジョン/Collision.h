//
//	@file	Collision.h
//	@brief	 ½θ»θΗNX
//	@date	2016/11/14
//	@author@gzεR

#pragma once
#include "Origin.h"
#include "./Mesh/CD3DXSKINMESH.h"
#include "./Mesh/CD3DXMESH.h"

#define RAY_DISTANCE 3

class Collision
{
	int hitCount_;
public:
	~Collision();
	Collision();

	int GetHitCnt() { return hitCount_; };
	int SetSpaceNo(D3DXVECTOR3 pos);
	bool CheckSpaceNo(int ownNo,int oppNo);
	bool CharaNear(D3DXVECTOR3 posA, D3DXVECTOR3 posB, float distance);
	//float Distance2(D3DXVECTOR3 posA, D3DXVECTOR3 posB);
	bool RayIntersect(CD3DXSKINMESH* Mesh_a, CD3DXMESH* Mesh_b ,float* pfDistance, D3DXVECTOR3* pvNormal/*,float* pfDistance*/);
	D3DXVECTOR3* SlideVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal);
	D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);
	HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices);
};

