//
//	@file	CharactorManager.h
//	@brief	�L�����N�^�[�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�m�ȍ��c

#pragma once
#include "./../Origin.h"
#include "./../Mesh/CD3DXMESH_ANIM.h"

class CharactorManager:public CD3DXMESH_ANIM
{
protected:
	virtual void Move(float speed) = 0;					//�ړ�
	virtual void Attack() = 0;							//�U��
	virtual void Dead() = 0;							//���S
	virtual void Motion_Update()=0;						//���[�V�����X�V
	void KnockBack(D3DXVECTOR3 atkPos, float distance);	//�m�b�N�o�b�N
	void Rotation(D3DXVECTOR3 dirVec);					//�L�����̉�]
	
public:
	CharactorManager();
	virtual ~CharactorManager() {};

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName)=0;		//�������E�ǂݍ���
	virtual void CharaUpdate()=0;								//�X�V
	void CharaRender(D3DXMATRIX mView,D3DXMATRIX mProj);		//�`��
	//void CharaDestroy();										//���
};

