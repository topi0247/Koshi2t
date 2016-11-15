//
//	@file	EnemyManager.h
//	@brief	�G�Ǘ��N���X
//	@date	2016/11/13
//	@outher	�g�z��R

#pragma once
#include "./../CharactorManager.h"
#include "./../../DebugDraw/D3D11_TEXT.h"

class EnemyManager : public CharactorManager
{
private:
	D3DXVECTOR3 targetPos_;
	enum TargetObject
	{
		princess = 0,
		player,
	};
	TargetObject targetObj;
protected:

	virtual void NormalAttack() = 0;	//�ʏ�U��
	virtual void Attack();				//�U��
	virtual void Move(float speed);		//�ړ�����
	virtual void Dead();				//���S
	virtual void Motion_Update() {};	//���[�V�����X�V
	void Spawn();						//�G�X�|�[��

public:
	EnemyManager() { m_vPos.z = 10; };
	virtual ~EnemyManager() {};
	
	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);		//�������E�ǂݍ���

	void CheckNearPlayer(D3DXVECTOR3 position);	//�߂��ɂ��邩����
	D3DXVECTOR3 GetOwnPos()const { return m_vPos; };
};

