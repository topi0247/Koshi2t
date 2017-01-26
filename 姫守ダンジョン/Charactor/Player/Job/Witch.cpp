//
//	@file	Witch.cpp
//	@brief	魔導士クラス
//	@date	2016/11/21
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#include "./Witch.h"


Witch::Witch(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	magicFlg_ = false;
	atkNo_ = noAtk;
	attackCount_ = 0;
	magic_ = new CD3DXMESH;
	magicSpeed_ = 3.0f;
	magic_ = creator_->LoadStage("魔法球");

	//UI
	jobMarkUI_ = new TD_Graphics;
	jobUIPos_ = D3DXVECTOR2(30 + charaType*UI_INTERVAL + UI_SPACE, 860);
	D3DXVECTOR2 scale(105, 100);
	jobMarkUI_->Init(L"./UI/UI_Tex/mage.png", jobUIPos_, scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	//Witch_UI["WITCH_UI"] = new TD_Graphics;
}

Witch::~Witch()
{
	delete magic_;
	magic_ = nullptr;
	delete jobMarkUI_;
	jobMarkUI_ = nullptr;
	//delete Witch_UI["WITCH_UI"];
	//magic_ = nullptr;
}



//
//	@brief	リセット
void Witch::Reset()
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
	magicFlg_ = false;

	m_Pos = D3DXVECTOR3(-2.25 + charaType_*1.5, 0, -10);
}


//
//	@brief	攻撃
void Witch::Attack()
{
	//atkNo_ = noAtk;
	if (/*magicFlg_ == false && */GamePad::checkInput(charaType_, GamePad::InputName::A)
		/*|| GetKeyState('1') & 0x80*/)
	{
		++attackCount_;
		//atkNo_ = waitAtk;
		moveAbleFlg_ = false;
	}
	else if (atkNo_ == normalAtk)
	{
		attackCount_ = 0;
		Normal_Attack();
	}
	else if (atkNo_ == charge)
	{
		attackCount_ = 0;
		atkNo_ = specialAtk;
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = FPS*param_->chargeTime_;
	static bool chargeMotionFlg = false;

	if (0 < attackCount_ && attackCount_ <= inputTime)
	{
		atkNo_ = normalAtk;
	}
	else if (inputTime < attackCount_)
	{
		atkNo_ = charge;
		moveAbleFlg_ = false;
		if (!chargeMotionFlg && motionNo_ != motion_->GetMotion("charge1")->id_)
		{
			motionChange_ = false;
			chargeMotionFlg = true;
			//motionNo_ = motion_->GetMotion("charge")->id_;
			//m_pD3dxMesh->ChangeAnimSet(motionNo_);
			//timeEnd_ = motion_->GetMotion("attack")->frame_;
			//motionSpeed_ = 1 / (float)timeEnd_;
			//motionCount_ = 0;
			ChangeMotion(motion_, "charge1");
		}
		else if (++motionCount_ > motionFrame_&& chargeMotionFlg &&  motionNo_ != motion_->GetMotion("charge2")->id_)
		{
			ChangeMotion(motion_, "charge2");
		}
	}

	if (atkNo_ == specialAtk)
	{
		chargeMotionFlg = false;
		Special_Attack();
	}


}

//
//	@brief	通常攻撃
void Witch::Normal_Attack()
{
	//float dist = param_->attackReach_;
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("attack1")->id_)
	{
		motionChange_ = false;
		//motionNo_ = motion_->GetMotion("attack")->id_;
		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//timeEnd_ = motion_->GetMotion("attack")->frame_;
		//motionSpeed_ = 1 / (float)timeEnd_;
		//motionCount_ = 0;
		ChangeMotion(motion_, "attack1");
	}

	if (++motionCount_ > motionFrame_)
	{
		Sound::getInstance().SE_play("M_NORMALATK");
		atkNo_ = noAtk;
		motionChange_ = true;
		moveAbleFlg_ = true;
		InstanceMagicBall(param_->attackRange_, param_->normalAtk_, true);
		Effect::getInstance().Effect_Play("magicball", m_Pos);
		Effect::getInstance().SetScale("magicball", 0.2);
	}


}

//
//	@brief	特殊攻撃
void Witch::Special_Attack()
{
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("attack1")->id_)
	{
		motionChange_ = false;
		//motionNo_ = motion_->GetMotion("attack")->id_;
		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//timeEnd_ = motion_->GetMotion("attack")->frame_;
		//motionSpeed_ = 1 / (float)timeEnd_;
		//motionCount_ = 0;
		ChangeMotion(motion_, "attack1");
	}

	if (++motionCount_ > motionFrame_)
	{
		Sound::getInstance().SE_play("M_NORMALATK");
		atkNo_ = noAtk;
		motionChange_ = true;
		moveAbleFlg_ = true;
		InstanceMagicBall(param_->attackRange_, param_->normalAtk_, false);
		Effect::getInstance().Effect_Play("magicball", m_Pos);
		Effect::getInstance().SetScale("magicball", 0.2);
		//RazorBeam();
	}


}

//
//	@brief	マジックボール生成
void Witch::InstanceMagicBall(float range, float atk, bool flg)
{
	//float kRange = param_->weaponHitReach_;
	float kDist = param_->knockbackDist_;
	float kSpeed = param_->knockbackSpeed_;
	if (!magicFlg_)
	{
		float angle = D3DXToDegree(m_Yaw);
		//for (int i = 0; i < magicBallCount_; i++)
		//{
		magicBall_ = new WeaponBall;
		/*int degree = 90 / (magicBallCount_ / 2 + 1);
		float temp = angle - 90 + degree + degree*i;
		temp = D3DXToRadian(temp);*/
		D3DXVECTOR3 vec(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);
		magicBall_->SetDir(vec);
		magicBall_->SetScale(0/*param_->weaponScale_*/);
		magicBall_->SetStartPos(D3DXVECTOR3(m_Pos.x, m_Pos.y + 1, m_Pos.z));
		//magicBall_->SetDamageList(allCharaList_, charaType_, 1);
		magicBall_->SetKnockBack(range, kDist, kSpeed, charaType_,Enemy);
		magicBall_->SetAttack(atk);
		magicBall_->SetHitSound("M_DAMAGE_HIT");
		magicBall_->SetHitDelFlg(flg);
		//}
		magicFlg_ = true;
	}
}

//
//	@brief	マジックボールの更新
void Witch::WeaponUpdate()
{
	if (magicFlg_)
	{
		magicBall_->Move_Weapon(magicSpeed_);
		//magicBall_->SetDamageList(allCharaList_, charaType_, 1);
		Effect::getInstance().Update("magicball", magicBall_->GetPosition());
		if (magicBall_->GetDelFlg())
		{
			magicFlg_ = false;
			delete magicBall_;
			magicBall_ = nullptr;
			//Effect::getInstance().Effect_Stop("magicball");

		}
	}

}

//
//	@brief	レーザービーム
void Witch::RazorBeam()
{
	magicSpeed_ = 1.0f;
	float kRange = param_->weaponHitReach_;
	float kDist = param_->knockbackDist_;
	float kSpeed = param_->knockbackSpeed_;
	if (!magicFlg_)
	{
		magicBall_ = new WeaponBall;
		D3DXVECTOR3 vec(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);
		magicBall_->SetDir(vec);
		magicBall_->SetScale(0);
		magicBall_->SetStartPos(D3DXVECTOR3(m_Pos.x, m_Pos.y, m_Pos.z));
		//magicBall_->SetDamageList(allCharaList_, charaType_, 1);
		magicBall_->SetKnockBack(kRange, kDist, kSpeed, charaType_,Enemy);
		magicBall_->SetAttack(param_->specialAtk_);
		magicBall_->SetHitSound("M_DAMAGE_HIT");
		magicBall_->SetHitDelFlg(false);

		magicFlg_ = true;
	}
}

//
//	@brief	被ダメ時のSE再生
void Witch::DamageSound()
{
	Sound::getInstance().SE_play("M_DAMAGE");
}

//
//	@brief	死亡音再生
void Witch::DeadSound()
{
	Sound::getInstance().SE_play("M_DEAD");
}

//
//	@brief	描画
void Witch::CharaRender()
{
	//D3DXVECTOR2 pos(0, 0);
	//D3DXVECTOR2 size(1, 1);
	//Witch_UI["WITCH_UI"]->Render(pos,size);

	//モデル描画
	mesh_->m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);
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
	//魔法描画
	if (magicFlg_)
	{
		magic_->Render(magicBall_->GetPosition(), D3DXVECTOR3(0, 0, 0), magicBall_->GetScale());
	}

	//Effect::getInstance().Draw();

	//UI描画
	UIRender();
}