//
//	@file	EnemyManager.cpp
//	@brief	エネミー管理クラス
//	@date	2016/11/13
//	@outher　吉越大騎

#include "EnemyManager.h"

//
//	@brief						Xファイル読み込み
//	@param (m_hWnd)				ウィンドウハンドル
//	@param (m_pDevice)			デバイス
//	@param (m_pDeviceContext)	デバイスコンテキスト
//	@param (fileName)			読み込むキャラ名
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
//	@brief			移動処理
//	@param (speed)	移動速度
void EnemyManager::Move(float speed)
{
	D3DXVECTOR3 E_Lock;
	E_Lock.x = targetPos_.x - m_vPos.x;
	E_Lock.z = targetPos_.z - m_vPos.z;

	//回転処理
	Rotation(E_Lock);
	float sp = speed;
	
	m_vPos += D3DXVECTOR3(E_Lock.x*sp,0, E_Lock.z*sp);
}

//
//	@brief	死亡処理
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
//	@brief	復活
void EnemyManager::Spawn()
{
}
