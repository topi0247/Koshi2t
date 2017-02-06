//
//	@file	Collision.h
//	@brief	あたり判定管理クラス
//	@date	2016/11/14
//	@author 吉越大騎
//	@note	空間分割による衝突判定追加(仁科香苗)

#pragma once
#include "Origin.h"
#include "./Mesh/CD3DXSKINMESH.h"
#include "./Mesh/CD3DXMESH.h"

#define RAY_DISTANCE 3			//レイを放つ距離
#define STAGE_SLIDE 64			//ステージX軸のマスの数
#define STAGE_SCALE { 68,0,36}	//ステージのスケール

class Collision
{
public:
	~Collision();
	Collision();

	//空間番号の取得
	int SetSpaceNo(D3DXVECTOR3 pos,int slide);	
	//空間番号による衝突判定
	bool CheckSpaceNo(int ownNo, int oppNo, int no, int slide);	
	//距離による衝突判定
	bool CharaNear(D3DXVECTOR3 posA, D3DXVECTOR3 posB, float distance);	
	//レイによる衝突判定
	bool RayIntersect(D3DXVECTOR3 pos, D3DXVECTOR3 dir, CD3DXMESH* Mesh_b, float* pfDistance, D3DXVECTOR3* pvNormal);	
	//滑りベクトル取得
	D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);	
	//レイの衝突地点のポリゴン頂点の発見
	HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices); 
};

