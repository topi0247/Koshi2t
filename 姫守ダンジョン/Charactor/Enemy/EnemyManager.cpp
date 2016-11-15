//
//	@file	EnemyManager.cpp
//	@brief	�G�l�~�[�Ǘ��N���X
//	@date	2016/11/13
//	@outher�@�g�z��R

#include "EnemyManager.h"

//
//	@brief						X�t�@�C���ǂݍ���
//	@param (m_hWnd)				�E�B���h�E�n���h��
//	@param (m_pDevice)			�f�o�C�X
//	@param (m_pDeviceContext)	�f�o�C�X�R���e�L�X�g
//	@param (fileName)			�ǂݍ��ރL������
void EnemyManager::CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName)
{
	char FileName[80] = { 0 };
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Enemy/");
	strcat_s(FileName, sizeof(FileName), fileName);
	if (FAILED(Init(m_hWnd, m_pDevice, m_pDeviceContext, FileName)))
	{
		return;
	}
}

void EnemyManager::CheckNearPlayer(D3DXVECTOR3 position)
{
	if (targetObj != player)
	{
		float range = 1.0f;
		double checkDist = range*range;
		if (pow(position.x - m_vPos.x, 2) + pow(position.z - m_vPos.z, 2) <= checkDist)
		{
			targetObj = player;
		}
	}

	targetPos_ = position;
}

//
//	@brief			�ړ�����
//	@param (speed)	�ړ����x
void EnemyManager::Move(float speed)
{
	D3DXVECTOR3 E_Lock;
	E_Lock.x = targetPos_.x - m_vPos.x;
	E_Lock.z = targetPos_.z - m_vPos.z;

	//��]����
	Rotation(E_Lock);
	float sp = speed;
	
	m_vPos += D3DXVECTOR3(E_Lock.x*sp,0, E_Lock.z*sp);
}

//
//	@brief	���S����
void EnemyManager::Dead()
{
}

//
//	@brief	
void EnemyManager::Attack()
{
	NormalAttack();
}

//
//	@brief	����
void EnemyManager::Spawn()
{
}
