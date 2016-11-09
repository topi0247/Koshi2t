//
//	@file	PlayerManager.cpp
//	@brief	プレイヤー管理クラス
//	@date	2016/11/09
//	@outher	仁科香苗

#include "PlayerManager.h"

//
//	@brief	コンストラクタ
PlayerManager::PlayerManager()
{
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
	Rotation(inputStick);

	//移動
	const float moveEpsilon = 0.2;	//誤作防止用
	float sp = 0;
	if (fabsf(inputStick.x) > moveEpsilon || fabsf(inputStick.z) > moveEpsilon)
	{
		sp = speed;
	}
	m_vPos += D3DXVECTOR3(inputStick.x*sp, 0, inputStick.z*sp);

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
	NormalAttack();
	SpecialAttack();
}

//
//	@brief	姫持ち上げ
void PlayerManager::Queen_Lite()
{

}

//
//	@brief	復活
void PlayerManager::Revival()
{
}