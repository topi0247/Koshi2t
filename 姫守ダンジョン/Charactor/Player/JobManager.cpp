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
	, attackCount_(0)
{
	atkNo_ = noAtk;

	//パラメータ初期化
	param_ = new PlayerParameter;
}

//
//	@brief	デストラクタ
JobManager::~JobManager()
{
	delete param_;
	param_ = nullptr;
}

//	
//	@brief	パラメータセット
void JobManager::SetParameter(JobParameter* param)
{
	memset(param_->name_,0, sizeof(param_->name_));
	memcpy(param_->name_, param->GetName(), sizeof(param_->name_));

	param_->hp_ = param->GetHP();
	param_->normalAtk_ = param->GetNormalAtk();
	param_->specialAtk_ = param->GetSpAtk();
	param_->def_ = param->GetDefence();
	param_->chargeTime_ = param->GetChargeTime();
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
	//周辺にいるキャラチェック
	AroundCharaCheck();

	//攻撃
	Attack();

	//モーション変更
	Motion_Update();

	//移動
	float speed = param_->moveSpeed_;
	Move(speed);

	//死亡
	if (aliveFlg_ == false)
	{
		Dead();
	}
}

