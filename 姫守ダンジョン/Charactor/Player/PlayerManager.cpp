//
//	@file	PlayerManager.cpp
//	@brief	�v���C���[�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�m�ȍ��c

#include "PlayerManager.h"


//
//	@brief						X�t�@�C���ǂݍ���
//	@param (m_hWnd)				�E�B���h�E�n���h��
//	@param (m_pDevice)			�f�o�C�X
//	@param (m_pDeviceContext)	�f�o�C�X�R���e�L�X�g
//	@param (fileName)			�ǂݍ��ރL������
void PlayerManager::CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName)
{
	char FileName[80] = { 0 };
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Player/");
	strcat_s(FileName, sizeof(FileName), fileName);
	if (FAILED(Init(m_hWnd, m_pDevice, m_pDeviceContext, FileName)))
	{
		return;
	}
}

//
//	@brief			�ړ�����
//	@param (speed)	�ړ����x
void PlayerManager::Move(float speed)
{
	//�X�e�B�b�N�̌X���擾
	D3DXVECTOR3 inputStick;
	inputStick.x = GamePad::getAnalogValue(controller_, GamePad::AnalogName::AnalogName_LeftStick_X);
	inputStick.z = GamePad::getAnalogValue(controller_, GamePad::AnalogName::AnalogName_LeftStick_Y);

	//��]����
	Rotation(inputStick);

	//�ړ�
	const float moveEpsilon = 0.2;	//���h�~�p
	float sp = 0;
	if (fabsf(inputStick.x) > moveEpsilon || fabsf(inputStick.z) > moveEpsilon)
	{
		sp = speed;
	}
	m_vPos += D3DXVECTOR3(inputStick.x*sp, 0, inputStick.z*sp);

	GamePad::update();
}

//
//	@brief	���S����
void PlayerManager::Dead()
{

}

//
//	@brief	
void PlayerManager::Attack()
{
	NormalAttack();
	SpecialAttack();
}


//
//	@brief	����
void PlayerManager::Revival()
{
}