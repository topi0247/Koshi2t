//
//	@file	JobManager.h
//	@brief	職業ごとの処理
//	@date	2016/11/10
//	@outher	仁科香苗

#include "JobManager.h"

//	
//	@brief	コンストラクタ
JobManager::JobManager(CharaType charaType)
	: hit(0)
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

	delete motion_;
	motion_ = nullptr;

	delete collision_;
	collision_ = nullptr;
}

//	
//	@brief	パラメータセット
void JobManager::SetParameter(JobParameter* param)
{
	memset(param_->name_, 0, sizeof(param_->name_));
	memcpy(param_->name_, param->GetName(), sizeof(param_->name_));

	param_->hp_ = param->GetHP();
	param_->normalAtk_ = param->GetNormalAtk();
	param_->specialAtk_ = param->GetSpAtk();
	param_->def_ = param->GetDefence();
	param_->chainWeapon_ = param->GetChainWeapon();
	param_->spChainWeapon_ = param->GetSpChainWeapon();
	param_->specialAttackTime_ = param->GetSpAtkTime();
	param_->invisibleTime_ = param->GetInvisivleTime();
	param_->weaponDelTime_ = param->GetWeaponDelTime();
	param_->chargeTime_ = param->GetChargeTime();
	param_->moveSpeed_ = param->GetMoveSpeed();
	param_->specialMoveSpeed_ = param->GetSpMoveSpeed();
	param_->weight_ = param->GetWeight();
	param_->attackReach_ = param->GetAttackReach();
	param_->attackRange_ = param->GetAttackRange();
	param_->specialAtkRange_ = param->GetSpAtkRange();
	param_->scale_ = param->GetScale();
	param_->knockbackSpeed_ = param->GetKnockBackSpeed();
	param_->knockbackDist_ = param->GetKnockBackDist();
	param_->weaponScale_ = param->GetWeaponScale();
	param_->weaponHitReach_ = param->GetWeaponHitReach();
	param_->weaponDelDist_ = param->GetWeaponDelDist();

	m_Scale = D3DXVECTOR3(param_->scale_, param_->scale_, param_->scale_);
	ownWright_ = param_->weight_;
	hp_ = param_->hp_;
}

//
//	@brief	キャラの更新
void JobManager::CharaUpdate()
{
	//周辺にいるキャラチェック
	AroundCharaCheck();


	//仮スピード
	//motionSpeed_ = 0.05;
	m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);
	//Motion_Update();

	//生存
	if (aliveFlg_ == true)
	{
		//移動
		float speed = param_->moveSpeed_;
		
		Move(speed);
		//攻撃
		Attack();

		//姫呼び
		Princess_Call();
	}
	//死亡
	else
	{
		Dead();

	}

	if (revivalFlg_ == true)
	{
		Revival();
	}
}

//
//	@brief	モーション更新
void JobManager::Motion_Update()
{
	if (motionChange_ == true)
	{
		switch (atkNo_)
		{
		case normalAtk:
			motionNo_ = motion_->GetMotion("attack1")->id_;
			motionChangeCount_ = motion_->GetMotion("attack1")->frame_;
			motionSpeed_ = 1 / (float)motionChangeCount_;
			m_pD3dxMesh->ChangeAnimSet(motionNo_);
			motionChange_ = false;
			break;
		default:
			break;
		}


	}

	if (motionChange_ == false && ++motionCount_ % motionChangeCount_ == 0)
	{
		motionChange_ = true;
		motionCount_ = 0;
		motionChangeCount_ = 0;
	}
}
