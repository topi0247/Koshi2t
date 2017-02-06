//
//	@file	Bomber.cpp
//	@brief	爆弾士クラス
//	@date	2016/11/21
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#include "./Bomber.h"

Bomber::Bomber(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	bombFlg_ = false;
	bombList_.clear();
	bombScale_ = 1;
	bombCount_ = 1;
	chargeMotionFlg_ = false;
	bomb_ = new CD3DXMESH;
	bomb_ = creator_->LoadStage("爆弾");

	//UI
	jobMarkUI_ = new TD_Graphics;
	jobUIPos_ = D3DXVECTOR2(0 + charaType*UI_INTERVAL + UI_SPACE, 910);
	D3DXVECTOR2 scale(136.5, 148);
	jobMarkUI_->Init(L"./UI/UI_Tex/icon_ranger.png", scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));


}

Bomber::~Bomber()
{
	delete bomb_;
	bomb_ = nullptr;
	delete jobMarkUI_;
	jobMarkUI_ = nullptr;
	//delete bom_UI["BOM_UI"];
	//bomb_ = nullptr;
}


////
////	@brief						Xファイル読み込み
////	@param (m_hWnd)				ウィンドウハンドル
////	@param (m_pDevice)			デバイス
////	@param (m_pDeviceContext)	デバイスコンテキスト
////	@param (fileName)			読み込むキャラ名
//const char* Bomber::CharaInit(const char* fileName)
//{
//	bomb_->Init("bomb.x");
//
//	bom_UI["BOM_UI"]->Init(L"./UI/UI_Tex/UIbom.png", 0, D3DXVECTOR2(1480, 785), D3DXVECTOR2(256, 128), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
//
//	char FileName[80] = { 0 };
//	memset(FileName, 0, sizeof(FileName));
//	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Player/");
//	strcat_s(FileName, sizeof(FileName), fileName);
//	return FileName;
//	//CreateFromX(FileName);
//	//m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
//	//ownWeight_ = 0.001f;
//}

//
//	@brief	リセット
void Bomber::Reset()
{
	hp_ = param_->hp_;
	motionCount_ = 0;
	motionChange_ = true;
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	aroundCharaList_.clear();
	allCharaList_.clear();
	atkNo_ = noAtk;
	revivalFlg_ = false;
	callTiming_ = 0;
	attackCount_ = 0;
	bombFlg_ = false;
	chargeMotionFlg_ = false;
	bombList_.clear();

	m_Pos = D3DXVECTOR3(-2.25 + charaType_*1.5, 0, -10);
}


//
//	@brief	攻撃
void Bomber::Attack()
{
	if (GamePad::checkInput(charaType_, GamePad::InputName::A)
		/*|| GetKeyState('1') & 0x80*/)
	{
		++attackCount_;
		moveAbleFlg_ = false;
	}
	else if (atkNo_ == normalAtk)
	{
		attackCount_ = 0;
		Normal_Attack();
	}
	else if (atkNo_ == charge)
	{
		moveAbleFlg_ = true;
		attackCount_ = 0;
		atkNo_ = specialAtk;
		//invinsibleFlg_ = true;
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = FPS*param_->chargeTime_;
	if (0 < attackCount_ && attackCount_ <= inputTime)
	{
		atkNo_ = normalAtk;
	}
	else if (inputTime < attackCount_)
	{
		atkNo_ = charge;
		moveAbleFlg_ = false;
		if (!chargeMotionFlg_ && motionNo_ != motion_->GetMotion("charge1")->id_)
		{
			motionChange_ = false;
			chargeMotionFlg_ = true;
			//motionNo_ = motion_->GetMotion("charge")->id_;
			//m_pD3dxMesh->ChangeAnimSet(motionNo_);
			//timeEnd_ = motion_->GetMotion("attack")->frame_;
			//motionSpeed_ = 1 / (float)timeEnd_;
			//motionCount_ = 0;
			ChangeMotion(motion_, "charge1");
			Sound::getInstance().SE_play("B_CHARGE");
			Effect::getInstance().Effect_Play("charge1",m_Pos);
		}
		else if (++motionCount_>motionFrame_ && chargeMotionFlg_ &&  motionNo_ != motion_->GetMotion("charge2")->id_)
		{
			ChangeMotion(motion_, "charge2");
		}
	}

	if (atkNo_ == specialAtk)
	{
		chargeMotionFlg_ = false;
		Effect::getInstance().Effect_Stop("charge1");
		Special_Attack();
	}

	/*if (invinsibleFlg_)
	{
		int invincibleTime = param_->specialAttackTime_;
		if (++invisibleCount_ % (FPS * invincibleTime) == 0)
		{
			invinsibleFlg_ = false;
			invisibleCount_ = 0;
		}
	}*/
}

//
//	@brief	通常攻撃
void Bomber::Normal_Attack()
{
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("attack")->id_)
	{
		motionChange_ = false;
		//motionNo_ = motion_->GetMotion("attack")->id_;
		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//timeEnd_ = motion_->GetMotion("attack")->frame_;
		//motionSpeed_ = 1 / (float)timeEnd_;
		//motionCount_ = 0;
		ChangeMotion(motion_, "attack");
	}

	float range = param_->attackRange_;
	float atk = param_->normalAtk_;
	InstanceWeapon(atk, range);

	//atkNo_ = noAtk;
}

//
//	@brief	特殊攻撃
void Bomber::Special_Attack()
{
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("special")->id_)
	{
		motionChange_ = false;
		/*motionNo_ = motion_->GetMotion("special")->id_;
		m_pD3dxMesh->ChangeAnimSet(motionNo_);
		timeEnd_ = motion_->GetMotion("special")->frame_;
		motionSpeed_ = 1 / (float)timeEnd_;
		motionCount_ = 0;*/
		ChangeMotion(motion_, "special");
	}
	float range = param_->specialAtkRange_;
	float atk = param_->specialAtk_;
	InstanceWeapon(atk,range);

	
}

//
//	@brief	爆弾の生成
void Bomber::InstanceWeapon(float atk, float range)
{
	size_t size = param_->chainWeapon_;
	//float range = param_->weaponHitReach_;
	float kDist = param_->knockbackDist_;
	float kSpeed = param_->knockbackSpeed_;
	moveAbleFlg_ = false;
	if (bombList_.empty())
	{
		effectPos_.clear();
	}
	if (motionCount_ == 0)
	{
		if (bombList_.empty() || bombList_.size() < size)
		{
			WeaponBall* bomb = new WeaponBall;
			bomb->SetStartPos(m_Pos);
			bomb->SetScale(param_->weaponScale_);
			bomb->SetAttack(atk);
			//bomb->SetDamageList(allCharaList_, charaType_,2);
			bomb->SetKnockBack(range, kDist, kSpeed, charaType_, Enemy);
			bomb->SetHitSound("B_DAMAGE_HIT");
			bombList_.push_back(bomb);
			effectPos_.push_back(m_Pos);
		}
	}
	if (++motionCount_>motionFrame_ )
	{
		Sound::getInstance().SE_play("B_SPECIAL");
		motionChange_ = true;
		
		atkNo_ = noAtk;
		moveAbleFlg_ = true;
		Sound::getInstance().SE_stop("B_CHARGE");
	}
	
}

//
//	@brief	爆弾の更新
void Bomber::WeaponUpdate()
{
	if (!bombList_.empty())
	{
		bombFlg_ = true;
		float delTime = FPS*param_->weaponDelTime_;
		for (auto b : bombList_)
		{
			b->Time_Del_Weapon(delTime);
			//b->SetDamageList(allCharaList_, charaType_,2);
		}
		if (/*b != nullptr &&*/ bombList_[0]->GetDelFlg())
		{
			Effect::getInstance().Effect_Play("n_explosion", effectPos_[0]);
			effectPos_.erase(effectPos_.begin());
			bombList_.erase(bombList_.begin());
			Sound::getInstance().SE_play("B_NORMALATK");
		}
		if (bombList_.empty())
		{
			bombList_.clear();
			bombFlg_ = false;
		}
	}
}

//
//	@brief	死亡音再生
void Bomber::DeadSound()
{
	Sound::getInstance().SE_play("B_DEAD");
}

//
//	@brief	描画
void Bomber::CharaRender()
{
	//モーション番号セット
	mesh_->m_pD3dxMesh->ChangeAnimSet(motionNo_);
	//再生地点をセット
	LPD3DXANIMATIONCONTROLLER anim = mesh_->m_pD3dxMesh->m_pAnimController;
	anim->SetTrackPosition(0, motionPlayPos_);
	//再生
	anim->AdvanceTime(motionSpeed_, NULL);
	//再生地点の更新
	motionPlayPos_ += motionSpeed_;

	

	//モデル描画
	bool drawFlg = true;
	if (damageFlg_)
	{
		if (++damageCount_ % 5 == 0)
		{
			drawFlg = false;
		}
	}
	if (drawFlg)
	{
		float scale = 0.2f;
		mesh_->Render(m_Pos, m_Yaw, D3DXVECTOR3(scale, scale, scale));
	}
	//爆弾の描画
	if (!bombList_.empty())
	{
		for (auto b : bombList_)
		{
			if (b != nullptr)
			{
				//b->Render();
				bomb_->Render(b->GetPosition(), D3DXVECTOR3(0, 0, 0), b->GetScale());
			}
		}
	}

	//Effect::getInstance().Draw();


	////UI描画
	//UIRender();
}