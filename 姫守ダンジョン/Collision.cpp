//
//	@file	Collision.cpp
//	@brief	�����蔻��Ǘ��N���X
//	@date	2016/11/14
//	@outher�@�g�z��R

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

	//���C���o�����b�V���̈ʒu�E��]�����C�ɓK�p
	vStart = Mesh_a->m_vPos;
	vEnd = D3DXVECTOR3(0, 0, 1);
	D3DXMatrixRotationY(&mRotation, Mesh_a->m_fYaw);
	D3DXVec3TransformCoord(&vEnd, &vEnd, &mRotation);
	vEnd += vStart;

	//���C�𓖂Ă郁�b�V���������Ă������]���Ă���ꍇ�ł��Ώۂ̃��[���h�s��̋t�s���p����ΐ��������C��������
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

