//
//	@file	JobManager.h
//	@brief	職業ごとの処理
//	@date	2016/11/10
//	@outher	仁科香苗

#include "JobManager.h"

//	
//	@brief	コンストラクタ
JobManager::JobManager(Controller controller)
	:timeCount_(0)
	, hit(0)
{
	atkNo_ = noAtk;
	SetParameter();
}

//
//	@brief	デストラクタ
JobManager::~JobManager()
{
}

//	
//	@brief	パラメータセット
void JobManager::SetParameter()
{
	paramRead_ = new ParameterRead;
	paramRead_->SetJobParameter("./ReadDate/JobParameterData.csv");

	//for(int i=0;i<paramRead_->get)
}

//
//	@brief	キャラの更新
void JobManager::CharaUpdate()
{
	m_pD3dxMesh->m_pAnimController->AdvanceTime(0.1, NULL);
	//周辺にいるキャラチェック
	ArouncCharaCheck();

	//攻撃
	Attack();
	/*if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		Attack();
	}*/

	//姫呼び
	if (GamePad::checkInput(controller_, GamePad::InputName::B))
	{
		callFlg_ = true;
		//Princess_Call();
	}

	//モーション変更
	Motion_Update();

	//移動
	Move(0.1);
}

////
////	@brief	モーション更新
//void JobManager::Motion_Update()
//{
//	m_pAnimController->AdvanceTime(0.001, NULL);
//
//	//攻撃
//	if (GamePad::checkInput(controller_, GamePad::InputName::A))
//	{
//		ChangeMotion(waitM);
//	}
//
//	//姫呼び
//	if (GamePad::checkInput(controller_, GamePad::InputName::B))
//	{
//		ChangeMotion(walkM);
//	}
//}

//
//	@brief	パラメータ取得
//PlayerParameter JobManager::GetParam()const
//{
//	//return playerParm_;
//}
