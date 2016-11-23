//
//	@file	PlayerManager.cpp
//	@brief	プレイヤー管理クラス
//	@date	2016/11/09
//	@outher	仁科香苗

#include "PlayerManager.h"


//
//	@brief						Xファイル読み込み
//	@param (m_hWnd)				ウィンドウハンドル
//	@param (m_pDevice)			デバイス
//	@param (m_pDeviceContext)	デバイスコンテキスト
//	@param (fileName)			読み込むキャラ名
void PlayerManager::CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName)
{
	char FileName[80] = { 0 };
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Player/");
	strcat_s(FileName, sizeof(FileName), fileName);
	CD3DXSKINMESH_INIT si;
	si.hWnd = m_hWnd;
	si.pDevice = m_pDevice;
	si.pDeviceContext = m_pDeviceContext;
	Init(&si);
	CreateFromX(FileName);
	m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
	//ownWright_ = 0.001f;
}

//
//	@brief			移動処理
//	@param (speed)	移動速度
void PlayerManager::Move(float speed)
{
	//スティックの傾き取得
	D3DXVECTOR3 inputStick;
	inputStick.x = GamePad::getAnalogValue(charaType_, GamePad::AnalogName::AnalogName_LeftStick_X);
	inputStick.z = GamePad::getAnalogValue(charaType_, GamePad::AnalogName::AnalogName_LeftStick_Y);

	//回転処理
	const float rotEpsilon = 0.3;
	if (fabsf(inputStick.x) > rotEpsilon || fabsf(inputStick.z) > rotEpsilon)
	{
		Rotation(inputStick);
	}


	//移動
	const float moveEpsilon = 0.2;	//誤作防止用
	float sp = 0;
	if (fabsf(inputStick.x) > moveEpsilon || fabsf(inputStick.z) > moveEpsilon)
	{
		sp = speed;
		if (motionNo_ != walkM)
		{
			motionNo_ = walkM;
			m_pD3dxMesh->ChangeAnimSet(walkM);
			//ChangeMotion(waitM);
		}
	}
	else
	{
		if (motionNo_ != waitM)
		{
			motionNo_ = waitM;
			m_pD3dxMesh->ChangeAnimSet(0);
			//ChangeMotion(walkM);
		}
	}

	//opponentWeight_ = 1;
	MoveCharaHit();

	m_Dir = D3DXVECTOR3(inputStick.x*sp * opponentWeight_, 0, inputStick.z*sp * opponentWeight_);
	//m_vPos += D3DXVECTOR3(inputStick.x*sp - opponentWeight_, 0, inputStick.z*sp - opponentWeight_);

	GamePad::update();

	//m_Dir = D3DXVECTOR3(m_AxisX.x, m_AxisY.y, m_AxisZ.z);
	//m_Dir = D3DXVECTOR3(m_Move.x, 0, m_Move.z);
}

//
//	@brief	ダメージ計算
void PlayerManager::DamageCalc(unsigned int atk)
{
	float damage = atk / (1 + ((float)param_->def_ / 100));

	if (hp_ <= damage)
	{
		hp_ = 0;
	}
	else
	{
		hp_ -= damage;
	}
}

//
//	@brief	死亡処理
void PlayerManager::Dead()
{
	
}

//
//	@brief	モーション更新
void PlayerManager::Motion_Update()
{
	const float speed = 0.01;
	m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);

	//m_pAnimController->AdvanceTime(speed, NULL);

	////攻撃
	//if (GamePad::checkInput(controller_, GamePad::InputName::A))
	//{
	//	//ChangeMotion(waitM);
	//}

	////姫呼び
	//if (GamePad::checkInput(controller_, GamePad::InputName::B))
	//{
	//	//ChangeMotion(walkM);
	//}
}


//
//	@brief	復活
void PlayerManager::Revival()
{
	aliveFlg_ = true;
}

//
//	@brief	姫呼び
void PlayerManager::Princess_Call()
{
	if (GamePad::checkInput(charaType_, GamePad::InputName::B))
	{
		moveAbleFlg_ = false;
	}
}

//
//	@brief	生存フラグ取得
bool PlayerManager::GetAliveFlg()const
{
	return aliveFlg_;
}