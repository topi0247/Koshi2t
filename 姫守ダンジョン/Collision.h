//
//	@file	Collision.h
//	@brief	Ç†ÇΩÇËîªíËä«óùÉNÉâÉX
//	@date	2016/11/14
//	@authorÅ@ãgâzëÂãR

#pragma once
#include "Origin.h"
#include "./Mesh/CD3DXSKINMESH.h"
#include "./Mesh/CD3DXMESH.h"

#define RAY_DISTANCE 3
#define STAGE_SLIDE 64
#define STAGE_SCALE { 68,0,36}

enum State
{
	Not = 0,
	Existence,
};

class Collision
{
	static int* stageSpace_;
	static int spaceAmount_;
public:
	~Collision();
	Collision();
	static void StageSlideInit();
	static void StageSpaceReset();
	static void SetSpaceNoArray(D3DXVECTOR3 pos);

	int SetSpaceNo(D3DXVECTOR3 pos,int slide);
	int GetStageSpace(int no);
	bool CheckSpaceNo(int ownNo, int oppNo, int no, int slide);
	bool CharaNear(D3DXVECTOR3 posA, D3DXVECTOR3 posB, float distance);
	float Distance2(D3DXVECTOR3 posA, D3DXVECTOR3 posB);
	bool RayIntersect(D3DXVECTOR3 pos, D3DXVECTOR3 dir, CD3DXMESH* Mesh_b, float* pfDistance, D3DXVECTOR3* pvNormal/*,float* pfDistance*/);
	D3DXVECTOR3* SlideVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal);
	D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);
	HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices);
};

