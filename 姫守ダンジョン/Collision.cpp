//
//	@file	Collision.cpp
//	@brief	あたり判定管理クラス
//	@date	2016/11/14
//	@author　吉越大騎

#include "Collision.h"

int* Collision::stageSpace_;
int Collision::spaceAmount_;


Collision::Collision()
{
	float fDistance = 0;
}


Collision::~Collision()
{
}

//
//	@brief	ステージ配列の設定
void Collision::StageSlideInit()
{
	//ステージスケール
	D3DXVECTOR3 stScale = STAGE_SCALE;
	int no = ((int)stScale.z / 2)*STAGE_SLIDE + (int)stScale.x / 2;

	stageSpace_ = new int[no];
	spaceAmount_ = no;
	for (int i = 0; i < no; i++)
	{
		stageSpace_[i] = Not;
	}
}

//
//	@brief			空間番号取得
//	@param(pos)		自身の座標
//	@param(slide)	最大分割数に除算する数。数字が大きいほど分割数が少なくなる
//	@note			1ステージ分だけ確認用に用意。
int Collision::SetSpaceNo(D3DXVECTOR3 pos, int slide)
{
	//x軸分割数
	int sx = STAGE_SLIDE / slide;

	//ステージスケール
	D3DXVECTOR3 stScale = STAGE_SCALE;

	//補正値(ステージスケールの半分)
	D3DXVECTOR3 correction = { stScale.x / 2,0,stScale.z / 2 };

	////ステージ座標
	//D3DXVECTOR3 stagePos = { 0,0,0 };
	////ステージ座標の補正
	//D3DXVECTOR3 tempStagePos = { stagePos.x + correction.x,0,stagePos.z + correction.z };

	//自身の座標補正
	D3DXVECTOR3 tempOwnPos = { pos.x + correction.x,0,pos.z + correction.z };
	//自身の補正された座標から、そのステージにおける空間番号を算出
	int no = ((int)tempOwnPos.z / slide)*sx + (int)tempOwnPos.x / slide;

	return no;
}

//
//	@brief		空間番号取得、ステージ配列にセット
//	@param(pos)	自身の座標
//	@return		配列に何もいなければセット。何かいたら-1を返す
void Collision::SetSpaceNoArray(D3DXVECTOR3 pos)
{
	//x軸分割数
	int sx = STAGE_SLIDE;

	//ステージスケール
	D3DXVECTOR3 stScale = STAGE_SCALE;

	//補正値(ステージスケールの半分)
	D3DXVECTOR3 correction = { stScale.x / 2,0,stScale.z / 2 };

	//自身の座標補正
	D3DXVECTOR3 tempOwnPos = { pos.x + correction.x,0,pos.z + correction.z };
	//自身の補正された座標から、そのステージにおける空間番号を算出
	int no = ((int)tempOwnPos.z / 2)*sx + (int)tempOwnPos.x / 2;

	stageSpace_[no] = Existence;
}

//
//	@brief	ステージ配列の更新
void Collision::StageSpaceReset()
{
	for (int i = 0; i < spaceAmount_; i++)
	{
		stageSpace_[i] = Not;
	}
}

//
//	@brief		ステージ配列の要素状態の取得
//	@param(no)	空間番号
//	@note		最大空間分割数で分割した時の空間番号
int Collision::GetStageSpace(int no)
{
	return stageSpace_[no];
}

//
//	@brief			周辺のキャラクターとの空間番号の確認
//	@param(ownNo)	自身の空間番号
//	@param(oppNo)	相手の空間番号
//	@param(no)		探索するマスの範囲(自分からの半径)
//	@param(slide)	最大分割数に除算する数。数字が大きいほど分割数が少なくなる
bool Collision::CheckSpaceNo(int ownNo, int oppNo,int no,int slide)
{
	//x軸の空間分割数
	int sx = STAGE_SLIDE/slide;

	//相手の空間番号が自分と自分の周辺の空間番号と一致するかどうか
	for (int i = -no; i <= no; i++)
	{
		int mz = ownNo - sx*i - no;
		int pz = ownNo - sx*i + no;
		if (mz <= oppNo && oppNo <=pz)
		{
			return true;
		}
	}

	/*if ((ownNo - 1 <= oppNo && oppNo <= ownNo + 1)
		|| (ownNo - sx - 1 <= oppNo && oppNo <= ownNo - sx + 1)
		|| (ownNo + sx - 1 <= oppNo && oppNo <= ownNo + sx + 1))
	{
		return true;
	}*/

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

//
//	@breif			距離測定
//	@param (posA)	自身の座標
//	@param (posB)	相手の座標
//	@return			距離の二乗
float Collision::Distance2(D3DXVECTOR3 posA, D3DXVECTOR3 posB)
{
	return pow(posA.x - posB.x, 2) + pow(posA.z - posB.z, 2);
}

bool Collision::RayIntersect(D3DXVECTOR3 pos, D3DXVECTOR3 dir, CD3DXMESH* pMeshB, float* pfDistance, D3DXVECTOR3* pvNormal)
{
	BOOL boHit = false;
	D3DXMATRIX Inv;
	D3DXVECTOR3 vStart/*, vEnd*/, vDirection;
	//レイを出すメッシュの位置・回転をレイに適用
	vStart = pos;
	vDirection = dir;
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

D3DXVECTOR3* Collision::SlideVector(D3DXVECTOR3 * out, const D3DXVECTOR3 & front, const D3DXVECTOR3 & normal)
{
	D3DXVECTOR3 normal_n;
	D3DXVec3Normalize(&normal_n, &normal);
	return D3DXVec3Normalize(out, &(front - D3DXVec3Dot(&front, &normal_n) * normal_n));
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


