//
//	@file	EnemyManager.cpp
//	@brief	エネミー管理クラス
//	@date	2016/11/13
//	@outher　吉越大騎

#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	m_Pos = { 0,0,0 };
	//targetPos_ = D3DXVECTOR3(0, 0, 0);
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
	CD3DXSKINMESH_INIT si;
	si.hWnd = m_hWnd;
	si.pDevice = m_pDevice;
	si.pDeviceContext = m_pDeviceContext;
	Init(&si);
	CreateFromX(FileName);
	m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
}

//
//	@brief　			ターゲット設定
//	@param (chara)		ターゲットにするキャラ
void EnemyManager::SetTarget(CharactorManager* chara)
{
	targetChar_ = chara;
	targetPos_ = targetChar_->m_Pos;
}

//
//	@brief　				ターゲットの更新
//	@param (chara)			プレイヤー
//	@param (princess)		姫
void EnemyManager::Target_Update(CharactorManager * chara, CharactorManager * princess)
{
	CharactorManager* temp = chara;
	if (targetChar_->GetCharaType() != temp->GetCharaType())
	{
		temp = targetChar_;
	}
	//現在のターゲットが姫
	if (targetChar_->GetCharaType() == princess->GetCharaType())
	{
		temp = chara;
	}
	////現在のターゲットが死んでいる
	//if (!targetChar_->GetAliveFlg())
	//{
	//	targetChar_ = princess;
	//}

	SetTarget(temp);
}

//
//	@brief　			ターゲットポジションの更新
//	@param (position)	座標
void EnemyManager::SetTargetChar(CharactorManager* checkChar, CharactorManager* princess)
{
	/*if (targetObj_ != player)
	{
		float range = 1.0f;
		double checkDist = range*range;
		if (collision_->CharaNear(m_Pos,position,checkDist))
		{
			targetObj_ = player;
		}
		else
		{
			virPos = D3DXVECTOR3(0, 0, 0);
		}
	}
	
	targetPos_ = virPos;*/
	//現在のターゲットとチェックするプレイヤーが一致するか
	if (targetChar_ == checkChar)
	{
		//チェックする(現在ターゲットのプレイヤー）が生存しているか
		if (checkChar->GetAliveFlg())
		{
			//ターゲット更新
			targetChar_ = checkChar;
			targetPos_ = targetChar_->m_Pos;
		}
		else        //しんどるやーん
		{
			//ターゲットを姫に変更
			targetChar_ = princess;
			targetPos_ = targetChar_->m_Pos;
		}
	}
	else if (targetChar_ == princess || targetChar_ == nullptr)       //現在のターゲットが姫
	{
		//近くに生きとるプレイヤーがいるかどうか(チェックするプレイヤーが生きている 且つ 距離が一定以内)
		if (checkChar->GetAliveFlg() && collision_->CharaNear(m_Pos, checkChar->m_Pos, 50.0))
		{
			//ターゲットをプレイヤーに変更
			targetChar_ = checkChar;
			targetPos_ = targetChar_->m_Pos;
		}
		else         //近くに生きとるプレイヤーがおらんがな(チェックするプレイヤーが生きていない 又は 距離遠いやんけ)
		{
			//ターゲット更新
			targetChar_ = princess;
			targetPos_ = targetChar_->m_Pos;
		}
	}
}

//
//	@brief			移動処理
//	@param (speed)	移動速度
void EnemyManager::Move(float speed)
{
	D3DXVECTOR3 E_Lock;
	E_Lock.x = targetPos_.x - m_Pos.x;
	E_Lock.z = targetPos_.z - m_Pos.z;

	D3DXVec3Normalize(&E_Lock, &E_Lock);

	//回転処理
	Rotation(E_Lock);

	//向いている角度から単位ベクトルを取得
	D3DXVECTOR3 vec = D3DXVECTOR3(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);

	float sp = speed;
	
	m_Dir = D3DXVECTOR3(vec.x*sp,0, vec.z*sp);
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
