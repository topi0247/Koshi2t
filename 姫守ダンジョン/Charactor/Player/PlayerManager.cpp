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
	ownWright_ = 0.001f;
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

	opponentWeight_ = 1;
	MoveCharaHit();

	m_Dir = D3DXVECTOR3(inputStick.x*sp * opponentWeight_, 0, inputStick.z*sp * opponentWeight_);
	//m_vPos += D3DXVECTOR3(inputStick.x*sp - opponentWeight_, 0, inputStick.z*sp - opponentWeight_);

	GamePad::update();

	//m_Dir = D3DXVECTOR3(m_AxisX.x, m_AxisY.y, m_AxisZ.z);
	//m_Dir = D3DXVECTOR3(m_Move.x, 0, m_Move.z);
}

//
//	@brief	死亡処理
void PlayerManager::Dead()
{

}

////
////	@brief	攻撃処理
//void PlayerManager::Attack()
//{
//	if (GamePad::checkInput(controller_, GamePad::InputName::A))
//	{
//		++attackCount_;
//		atkNo_ = waitAtk;
//	}
//	else if(atkNo_!=noAtk)
//	{
//		//unsigned int inputTime = playerParam_.chargeTime_;
//		unsigned int inputTime = 40;
//		if (1 < attackCount_&& attackCount_ < inputTime)
//		{
//			atkNo_=normalAtk,
//			Normal_Attack();
//		}
//		else if (inputTime < attackCount_)
//		{
//			atkNo_ = specialAtk;
//			Special_Attack();
//		}
//	}
//	else if (atkNo_ == noAtk)
//	{
//		attackCount_ = 0;
//	}
//	//char str[256];
//	//sprintf(str, "A : %d", attackCount_);
//	//debugText_->Render(str, 0, 10);
//}

//
//	@brief	モーション更新
void PlayerManager::Motion_Update()
{
	const float speed = 0.01;

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

////
////	@brief	姫呼び
//D3DXVECTOR3 PlayerManager::Princess_Call()
//{
//	return m_vPos;
//}

//
//	@brief	生存フラグ取得
bool PlayerManager::GetAliveFlg()const
{
	return aliveFlg_;
}