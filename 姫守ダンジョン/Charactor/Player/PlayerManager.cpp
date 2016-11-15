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
	if (FAILED(Init(m_hWnd, m_pDevice, m_pDeviceContext, FileName)))
	{
		return;
	}


}

//
//	@brief			移動処理
//	@param (speed)	移動速度
void PlayerManager::Move(float speed)
{
	//スティックの傾き取得
	D3DXVECTOR3 inputStick;
	inputStick.x = GamePad::getAnalogValue(controller_, GamePad::AnalogName::AnalogName_LeftStick_X);
	inputStick.z = GamePad::getAnalogValue(controller_, GamePad::AnalogName::AnalogName_LeftStick_Y);

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
		if (motionNo_ != waitM)
		{
			motionNo_ = waitM;
			ChangeMotion(waitM);
		}
	}
	else
	{
		if (motionNo_ != walkM)
		{
			motionNo_ = walkM;
			ChangeMotion(walkM);
		}
	}
	m_vPos += D3DXVECTOR3(inputStick.x*sp, 0, inputStick.z*sp);

	GamePad::update();
}

//
//	@brief	死亡処理
void PlayerManager::Dead()
{

}

//
//	@brief	
void PlayerManager::Attack()
{
	if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		Normal_Attack();
		Special_Attack();
	}
}

//
//	@brief	モーション更新
void PlayerManager::Motion_Update()
{
	const float speed = 0.01;
	m_pAnimController->AdvanceTime(speed, NULL);

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