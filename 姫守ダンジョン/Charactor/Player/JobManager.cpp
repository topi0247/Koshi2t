//
//	@file	JobManager.h
//	@brief	職業ごとの処理
//	@date	2016/11/10
//	@outher	仁科香苗

#include "JobManager.h"

//	
//	@brief	コンストラクタ
JobManager::JobManager(CharaType charaType)
	:timeCount_(0)
	, hit(0)
{
	atkNo_ = noAtk;
}

//
//	@brief	デストラクタ
JobManager::~JobManager()
{
}

//	
//	@brief	パラメータセット
void JobManager::SetParameter(JobParameter* param)
{
	memset(param_->name_,0, sizeof(param_->name_));
	strcpy_s(param_->name_, sizeof(param_->name_), param->GetName());

	param_->hp_ = param->GetHP();
	param_->normalAtk_ = param->GetNormalAtk();
	param_->specialAtk_ = param->GetSpAtk();
	param_->def_ = param->GetDefense();
	param_->specialAttackTime_ = param->GetWaitTime();
	param_->hp_ = param->GetChargeTime();
	param_->moveSpeed_ = param->GetMoveSpeed();
	param_->specialMoveSpeed_ = param->GetSpMoveSpeed();
	param_->weight_ = param->GetWeight();
	param_->attackReach_ = param->GetAttackReach_();
	param_->attackRange_ = param->GetAttackRange_();
	param_->scale_ = param->GetScale();

	ownWright_ = param_->weight_;
	hp_ = param_->hp_;
}

//
//	@brief	キャラの更新
void JobManager::CharaUpdate()
{
	m_pD3dxMesh->m_pAnimController->AdvanceTime(0.1, NULL);
	//周辺にいるキャラチェック
	AroundCharaCheck();

	//攻撃
	Attack();
	/*if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		Attack();
	}*/

	//姫呼び
	if (GamePad::checkInput(charaType_, GamePad::InputName::B))
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
