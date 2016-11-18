//
//	@file	EnemyManager.cpp
//	@brief	エネミー管理クラス
//	@date	2016/11/13
//	@outher　吉越大騎

#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	m_vPos = { 0,0,0 };
	collision_ = new Collision;
}

EnemyManager::~EnemyManager()
{
	delete collision_;
	collision_ = nullptr;
}

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

//
//	@brief　			ターゲットポジションの更新
//	@param (position)	座標
//void EnemyManager::SetTargetChar(CharactorManager* checkChar, CharactorManager* princess)
//{
//	/*if (targetObj_ != player)
//	{
//		float range = 1.0f;
//		double checkDist = range*range;
//		if (collision_->CharaNear(m_vPos,position,checkDist))
//		{
//			targetObj_ = player;
//		}
//		else
//		{
//			virPos = D3DXVECTOR3(0, 0, 0);
//		}
//	}
//	
//	targetPos_ = virPos;*/
//	//現在のターゲットとチェックするプレイヤーが一致するか
//	if (targetChar_ == checkChar)
//	{
//		//チェックする(現在ターゲットのプレイヤー）が生存しているか
//		if (checkChar->GetAliveFlg())
//		{
//			//ターゲット更新
//			targetChar_ = checkChar;
//		}
//		else        //しんどるやーん
//		{
//			//ターゲットを姫に変更
//			targetChar_ = princess;
//		}
//	}
//	else if (targetChar_ == princess || targetChar_ == nullptr)       //現在のターゲットが姫
//	{
//		//近くに生きとるプレイヤーがいるかどうか(チェックするプレイヤーが生きている 且つ 距離が一定以内)
//		if (checkChar->GetAliveFlg() && collision_->CharaNear(m_vPos, checkChar->m_vPos, 50.0))
//		{
//			//ターゲットをプレイヤーに変更
//			targetChar_ = checkChar;
//		}
//		else         //近くに生きとるプレイヤーがおらんがな(チェックするプレイヤーが生きていない 又は 距離遠いやんけ)
//		{
//			//ターゲット更新
//			targetChar_ = princess;
//		}
//	}
//}

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
	
	m_Dir += D3DXVECTOR3(E_Lock.x*sp,0, E_Lock.z*sp);
}

//
//	@brief	死亡処理
void EnemyManager::Dead()
{
}

//
//	@brief	敵通常攻撃
void EnemyManager::Attack()
{
	NormalAttack();
}
