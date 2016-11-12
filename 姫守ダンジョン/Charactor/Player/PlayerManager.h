//
//	@file	PlayerManager.h
//	@brief	�v���C���[�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�m�ȍ��c
#pragma once
#include "./../CharactorManager.h"
#include "./GamePad.h"
#include "./../../DebugDraw/D3D11_TEXT.h"

enum Controller
{
	player1 = 0,
	player2,
	player3,
	player4,
};

class PlayerManager : public CharactorManager
{


protected:

	Controller controller_;	//Controller�ԍ�

	virtual void NormalAttack() = 0;	//�ʏ�U��
	virtual void SpecialAttack() = 0;	//����U��
	virtual void Attack();				//�U��
	virtual void Move(float speed);		//�ړ�����
	virtual void Dead();				//���S
	virtual void Motion_Update() {};	//���[�V�����X�V
	void Revival();						//����
public:
	PlayerManager() {};
	virtual ~PlayerManager() {};

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);
};