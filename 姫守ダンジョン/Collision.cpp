//
//	@file	Collision.cpp
//	@brief	あたり判定管理クラス
//	@date	2016/11/14
//	@author　吉越大騎

#include "Collision.h"



Collision::Collision()
{
	float fDistance = 0;
}


Collision::~Collision()
{
}

//bool Collision::RayIntersect(CD3DXMESH_ANIM* Mesh_a, CD3DXMESH_ANIM* Mesh_b,float* fDistance)
//{
//	BOOL boHit = false;
//	D3DXMATRIX mWorld, mRotation, Inv;
//	D3DXVECTOR3 vStart, vEnd, vDirection;
//
//	//レイを出すメッシュの位置・回転をレイに適用
//	vStart = Mesh_a->m_vPos;
//	vEnd = D3DXVECTOR3(0, 0, 1);
//	D3DXMatrixRotationY(&mRotation, Mesh_a->m_fYaw);
//	D3DXVec3TransformCoord(&vEnd, &vEnd, &mRotation);
//	vEnd += vStart;
//
//	//レイを当てるメッシュが動いていたり回転している場合でも対象のワールド行列の逆行列を用いれば正しくレイが当たる
//	D3DXMatrixTranslation(&mWorld, Mesh_b->m_vPos.x, Mesh_b->m_vPos.y, Mesh_b->m_vPos.z);
//	D3DXMatrixInverse(&mWorld, NULL, &mWorld);
//	D3DXVec3TransformCoord(&vStart, &vStart, &mWorld);
//	D3DXVec3TransformCoord(&vEnd, &vEnd, &mWorld);
//
//	/*float fDistance = 0;*/
//	DWORD dwIndex = 0;
//	D3DXVECTOR3 vIntersect;
//
//	vDirection = vEnd - vStart;
//	D3DXIntersect(Mesh_b->m_pMesh, &vStart, &vDirection, &boHit, NULL, NULL, NULL, fDistance, NULL, NULL);
//	if (boHit)
//	{
//		return true;
//	}
//	return false;
//}	
//
//
// L:入射ベクトル（レイ） N:ポリゴンの法線

//
//	@brief		空間番号取得
//	@param(pos)	自身の座標
//	@note       1ステージ分だけ確認用に用意。変更しやすいよう要修正
int Collision::SetSpaceNo(D3DXVECTOR3 pos)
{
	//x軸分割数
	int sx = 34;

	//ステージスケール
	D3DXVECTOR3 stScale = { 34 * 2,0,18 * 2 };

	//補正値(ステージスケールの半分)
	D3DXVECTOR3 correction = { stScale.x / 2,0,stScale.z / 2 };

	////ステージ座標
	//D3DXVECTOR3 stagePos = { 0,0,0 };
	////ステージ座標の補正
	//D3DXVECTOR3 tempStagePos = { stagePos.x + correction.x,0,stagePos.z + correction.z };

	//自身の座標補正
	D3DXVECTOR3 tempOwnPos = { pos.x + correction.x,0,pos.z + correction.z };
	//自身の補正された座標から、そのステージにおける空間番号を算出
	int no = ((int)tempOwnPos.z / 2)*sx + (int)tempOwnPos.x / 2;

	return no;
}

//
//	@brief	周辺のキャラクターとの空間番号の確認
bool Collision::CheckSpaceNo(int ownNo, int oppNo)
{
	//x軸の空間分割数
	int sx = 34;

	//相手の空間番号が自分と自分の周辺の空間番号と一致するかどうか
	if ((ownNo - 1 <= oppNo && oppNo <= ownNo + 1)
		|| (ownNo - sx - 1 <= oppNo && oppNo <= ownNo - sx + 1)
		|| (ownNo + sx - 1 <= oppNo && oppNo <= ownNo + sx + 1))
	{
		return true;
	}

	return false;
}

//
//	@brief				距離による衝突判定
//	@param(posA)		自身の座標
//	@param(posB)		相手の座標
//	@param(distance)	判定距離
bool Collision::CharaNear(D3DXVECTOR3 posA, D3DXVECTOR3 posB, float distance)
{
	float x = pow(posA.x - posB.x, 2);
	float z = pow(posA.z - posB.z, 2);
	float d1 = x + z;
	float d2 = pow(distance, 2);
	if (d1 <= d2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

////
////	@breif			距離測定
////	@param (posA)	自身の座標
////	@param (posB)	相手の座標
////	@return			距離の二乗
//float Collision::Distance2(D3DXVECTOR3 posA, D3DXVECTOR3 posB)
//{
//	return pow(posA.x - posB.x, 2) + pow(posA.z - posB.z, 2);
//}

bool Collision::RayIntersect(CD3DXSKINMESH* pMeshA, CD3DXMESH* pMeshB, float* pfDistance, D3DXVECTOR3* pvNormal)
{
	BOOL boHit = false;
	D3DXMATRIX Inv;
	D3DXVECTOR3 vStart, vEnd, vDirection;
	//レイを出すメッシュの位置・回転をレイに適用
	vStart = pMeshA->m_Pos;
	vDirection = pMeshA->m_Dir;
	//レイを当てるメッシュが動いていたり回転している場合でも対象のワールド行列の逆行列を用いれば正しくレイが当たる
	D3DXMatrixInverse(&Inv, NULL, &pMeshB->m_World);
	D3DXVec3TransformCoord(&vStart, &vStart, &Inv);

	D3DXVec3Normalize(&vDirection, &vDirection);
	DWORD dwIndex = 0;
	D3DXIntersect(pMeshB->m_pMesh, &vStart, &vDirection, &boHit, &dwIndex, NULL, NULL, pfDistance, NULL, NULL);
	if (boHit)
	{
		//交差しているポリゴンの頂点を見つける
		D3DXVECTOR3 vVertex[3];
		FindVerticesOnPoly(pMeshB->m_pMesh, dwIndex, vVertex);
		D3DXPLANE p;
		//その頂点から平面方程式を得る
		D3DXPlaneFromPoints(&p, &vVertex[0], &vVertex[1], &vVertex[2]);
		//平面方程式の係数が法線の成分
		pvNormal->x = p.a;
		pvNormal->y = p.b;
		pvNormal->z = p.c;
		return true;
	}
	return false;
}

D3DXVECTOR3 Collision::Slip(D3DXVECTOR3 L, D3DXVECTOR3 N)
{
	D3DXVECTOR3 S; //滑りベクトル（滑る方向）

	//滑りベクトル S=L-(N * L)/(|N|^2)*N
	S = L - ((D3DXVec3Dot(&N, &L)) / (pow(D3DXVec3Length(&N), 2)))*N;
	S.y = 0;

	return S;
}
//
//
//そのポリゴンの頂点を見つける
HRESULT Collision::FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices)
{
	DWORD i, k;
	DWORD dwStride = pMesh->GetNumBytesPerVertex();
	DWORD dwVertexNum = pMesh->GetNumVertices();
	DWORD dwPolyNum = pMesh->GetNumFaces();
	DWORD* pwPoly = NULL;
	pMesh->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);

	BYTE *pbVertices = NULL;
	FLOAT* pfVetices = NULL;
	LPDIRECT3DVERTEXBUFFER9 VB = NULL;
	pMesh->GetVertexBuffer(&VB);
	if (SUCCEEDED(VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{
		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3]];
		pvVertices[0].x = pfVetices[0];
		pvVertices[0].y = pfVetices[1];
		pvVertices[0].z = pfVetices[2];

		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 1]];
		pvVertices[1].x = pfVetices[0];
		pvVertices[1].y = pfVetices[1];
		pvVertices[1].z = pfVetices[2];

		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 2]];
		pvVertices[2].x = pfVetices[0];
		pvVertices[2].y = pfVetices[1];
		pvVertices[2].z = pfVetices[2];

		pMesh->UnlockIndexBuffer();
		VB->Unlock();
	}
	return S_OK;
}


