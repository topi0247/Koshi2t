//
//	@file	Collision.cpp
//	@brief	あたり判定管理クラス
//	@date	2016/11/14
//	@outher　吉越大騎

#include "Collision.h"



Collision::Collision()
{
	float fDistance = 0;
}


Collision::~Collision()
{
}

bool Collision::RayIntersect(CD3DXMESH_ANIM* Mesh_a, CD3DXMESH_ANIM* Mesh_b,float* fDistance)
{
	BOOL boHit = false;
	D3DXMATRIX mWorld, mRotation;
	D3DXVECTOR3 vStart, vEnd, vDirection;

	//レイを出すメッシュの位置・回転をレイに適用
	vStart = Mesh_a->m_vPos;
	vEnd = D3DXVECTOR3(0, 0, 1);
	D3DXMatrixRotationY(&mRotation, Mesh_a->m_fYaw);
	D3DXVec3TransformCoord(&vEnd, &vEnd, &mRotation);
	vEnd += vStart;

	//レイを当てるメッシュが動いていたり回転している場合でも対象のワールド行列の逆行列を用いれば正しくレイが当たる
	D3DXMatrixTranslation(&mWorld, Mesh_b->m_vPos.x, Mesh_b->m_vPos.y, Mesh_b->m_vPos.z);
	D3DXMatrixInverse(&mWorld, NULL, &mWorld);
	D3DXVec3TransformCoord(&vStart, &vStart, &mWorld);
	D3DXVec3TransformCoord(&vEnd, &vEnd, &mWorld);

	/*float fDistance = 0;*/
	DWORD dwIndex = 0;
	D3DXVECTOR3 vIntersect;

	vDirection = vEnd - vStart;
	D3DXIntersect(Mesh_b->m_pMesh, &vStart, &vDirection, &boHit, NULL, NULL, NULL, fDistance, NULL, NULL);
	if (boHit)
	{
		return true;
	}
	return false;
}	

