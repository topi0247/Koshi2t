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

	//UI
	backUI_ = new TD_Graphics;
	backUIPos_ = D3DXVECTOR2(0 + charaType * UI_INTERVAL + UI_SPACE, 910);
	D3DXVECTOR2 backScale(431.5, 148);
	switch (charaType)
	{
	case Player1:
		backUI_->Init(L"./UI/UI_Tex/hp1.png", backScale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
		break;
	case Player2:
		backUI_->Init(L"./UI/UI_Tex/hp2.png",backScale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
		break;
	case Player3:
		backUI_->Init(L"./UI/UI_Tex/hp3.png",backScale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
		break;
	case Player4:
		backUI_->Init(L"./UI/UI_Tex/hp4.png", backScale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
		break;
	}
	hpGageUI_ = new TD_Graphics;
	hpGazePos_ = D3DXVECTOR2(130 + charaType*UI_INTERVAL + UI_SPACE, 995);
	D3DXVECTOR2 hpScale(290, 60);
	hpGageUI_->Init(L"./UI/UI_Tex/HP_gage.png",hpScale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));

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

	delete backUI_;
	backUI_ = nullptr;

	delete hpGageUI_;
	hpGageUI_ = nullptr;
}

//
//	@brief	キャラの更新
void JobManager::CharaUpdate()
{
	//空間番号の更新
	spaceNo_ = collision_->SetSpaceNo(m_Pos, 2);

	//周辺にいるキャラチェック
	AroundCharaCheck();


	//仮スピード
	//motionSpeed_ = 0.05;
	//Motion_Update();

	//生存
	if (aliveFlg_ == true)
	{
		//移動
		//if (moveAbleFlg_ == true)
		//{
		float speed = param_->moveSpeed_;
		Move(speed);
		//}

		//攻撃
		if (!callFlg_)
		{
			Attack();
		}
		//姫呼び
		Princess_Call();
	}
	//死亡
	else if (!revivalFlg_)
	{
		Dead();
	}

	//ダメージを食らったときコントローラの振動
	if (damageFlg_)
	{
		GamePad::setVibration(charaType_);
	}
	else
	{
		GamePad::stopVibration(charaType_);
	}

	//飛び道具の更新
	WeaponUpdate();

	//蘇生
	if (revivalFlg_)
	{
		Revival();
	}
}

//
//	@brief	UI描画
void JobManager::UIRender()
{
	D3DXVECTOR2 scale(1, 1);
	backUI_->Render(backUIPos_, scale, true);
	jobMarkUI_->Render(jobUIPos_, scale, true);
	float hpX = (float)hp_ / (float)param_->hp_;
	scale = D3DXVECTOR2(hpX, 1);
	hpGageUI_->Render(hpGazePos_, scale, true);
}