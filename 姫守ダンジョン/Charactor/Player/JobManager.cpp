//
//	@file	JobManager.cpp
//	@brief	職業ごとの処理
//	@date	2016/11/10
//	@author	仁科香苗

#include "JobManager.h"

//	
//	@brief	コンストラクタ
JobManager::JobManager(CharaType charaType)
	: attackCount_(0)
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
//	@brief	キャラの更新
void JobManager::CharaUpdate()
{
	//空間番号の更新
	spaceNo_ = collision_->SetSpaceNo(m_Pos);

	//周辺にいるキャラチェック
	AroundCharaCheck();


	//仮スピード
	//motionSpeed_ = 0.05;
	mesh_->m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);
	//Motion_Update();

	//生存
	if (aliveFlg_ == true)
	{
		//移動
		if (moveAbleFlg_ == true)
		{
			float speed = param_->moveSpeed_;
			Move(speed);
		}

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

	//飛び道具の更新
	WeaponUpdate();

	//蘇生
	if (revivalFlg_ == true)
	{
		Revival();
	}
}

