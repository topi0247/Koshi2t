//
//	@file	SwordMan.cpp
//	@brief	åïémÉNÉâÉX
//	@date	2016/11/21
//	@author	êmâ»çÅïc
//	@author	ãgâzëÂãR(ÉTÉEÉìÉh)

#include "./SwordMan.h"


SwordMan::SwordMan(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	chainCount_ = 0;
	atkMotion_[0] = "attack1";
	atkMotion_[1] = "attack2";
	atkMotion_[2] = "attack3";
	atkMotion_[3] = "attack4";
	atkMotion_[4] = "attack5";
	atkMotion_[5] = "attack6";

	//UI
	jobMarkUI_ = new TD_Graphics;
	jobUIPos_ = D3DXVECTOR2(30 + charaType*UI_INTERVAL + UI_SPACE, 860);
	D3DXVECTOR2 scale(105, 100);
	jobMarkUI_->Init(L"./UI/UI_Tex/fighter.png", jobUIPos_, scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));

}

SwordMan::~SwordMan()
{
	delete jobMarkUI_;
	jobMarkUI_ = nullptr;
}


//
//	@brief	ÉäÉZÉbÉg
void SwordMan::Reset()
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
	chainCount_ = 0;
	m_Pos = D3DXVECTOR3(-2.25 + charaType_*1.5, 0, -10);
}


//
//	@brief	çUåÇ
void SwordMan::Attack()
{
	static int keyWait = 0;
	int maxKeyWait = 10;
	static bool atkAble = true;
	if (atkAble && GamePad::checkInput(charaType_, GamePad::InputName::A))
	{
		keyWait = 0;
		//++attackCount_;
		atkNo_ = normalAtk;
		atkAble = false;
		moveAbleFlg_ = false;
		//keyWait = 0;
	}
	else if (!atkAble && !GamePad::checkInput(charaType_, GamePad::InputName::A))
	{
		atkAble = true;
	}
	//else if (atkNo_ == normalAtk)
	//{
	//	attackCount_ = 0;
	//	motionCount_ = 0;
	//	atkNo_ = noAtk;
	//	Normal_Attack();
	//	hit = false;
	//	atkNo_ = noAtk;
	//	Special_Attack();
	//}
	else if (atkNo_ == noAtk)
	{
		if (++keyWait > maxKeyWait)
		{
			chainCount_ = 0;
		}
	}

	//if (!atkAble)
	//{
	//	if (++keyWait > maxKeyWait)
	//	{
	//		atkAble = true;
	//	}
	//}

	//else if (atkNo_ == charge)
	//{
	//	attackCount_ = 0;
	//	motionCount_ = 0;
	//	motionChange_ = true;
	//	atkNo_ = specialAtk;
	//}
	//unsigned int inputTime = playerParam_.chargeTime_;

	///* èCê≥ÇÃïKóvÇ†ÇË */
	//unsigned int inputTime = motionSpeed_;

	//if (0 < attackCount_ && attackCount_ <= inputTime)
	//{
	//	atkNo_ = normalAtk;
	//}


	if (atkNo_ == normalAtk)
	{
		Normal_Attack();
	}
}

//
//	@breif	í èÌçUåÇ
void SwordMan::Normal_Attack()
{
	if (motionChange_ == true && motionNo_ != motion_->GetMotion(atkMotion_[chainCount_%ChainAmount])->id_)
	{
		Sound::getInstance().SE_play("S_NORMALATK");
		motionChange_ = false;
		ChangeMotion(motion_, atkMotion_[chainCount_%ChainAmount]);
		Normal_Attack_Collision();
	}

	if (++motionCount_ > motionFrame_)
	{
		atkNo_ = noAtk;
		//attackCount_ = 0;
		++chainCount_;
		motionCount_ = 0;
		motionChange_ = true;
		moveAbleFlg_ = true;

		float speed = -0.3;
		D3DXVECTOR3 dir(sinf(m_Yaw)*speed, 0, cosf(m_Yaw)*speed);
		m_Dir = dir;
	}
}

//
//	@brief	í èÌçUåÇìñÇΩÇËîªíË
void SwordMan::Normal_Attack_Collision()
{
	float degree = D3DXToDegree(m_Yaw);
	float atkDist = param_->attackReach_;
	float hitAngle = param_->attackRange_;
	float backDist = param_->knockbackDist_;
	float speed = param_->knockbackSpeed_;

	if (!aroundCharaList_.empty())
	{
		for (auto chara : aroundCharaList_)
		{
			if (collision_->CharaNear(m_Pos, chara->m_Pos, atkDist))
			{
				D3DXVECTOR3 vec = chara->m_Pos - m_Pos;
				D3DXVec3Normalize(&vec, &vec);
				float angle = (atan2(vec.z, vec.x)*-1) - (D3DX_PI / 2.0f);
				angle = D3DXToDegree(angle);

				if (fabsf(degree - angle) <= hitAngle)
				{
					chara->SetKnockBack(m_Pos, backDist, speed, charaType_);
					if (chara->GetCharaType() == Enemy)
					{
						//ìGÇ…É_ÉÅÅ[ÉWÇ™ì¸Ç¡ÇΩéûÇÃSE
						Sound::getInstance().SE_play("S_DAMAGE_HIT");
						chara->DamageCalc(param_->normalAtk_);
					}
				}
			}
		}
	}
}

void SwordMan::DamageSound()
{
	Sound::getInstance().SE_play("S_DAMAGE");
}

////
////	@brief	ì¡éÍçUåÇ
//void SwordMan::Special_Attack()
//{
//	Special_Attack_Collision();
//
//	if (motionChange_ == true && motionNo_ != motion_->GetMotion("special")->id_)
//	{
//		Sound::getInstance().SE_play("S_SPECIAL");
//
//		motionChange_ = false;
//		//motionNo_ = motion_->GetMotion("special")->id_;
//		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
//		//timeEnd_ = motion_->GetMotion("special")->frame_;
//		//motionSpeed_ = 1 / (float)timeEnd_;
//		ChangeMotion(motion_, "special");
//	}
//
//	if (++motionCount_ > motionFrame_)
//	{
//		atkNo_ = noAtk;
//		//attackCount_ = 0;
//		motionCount_ = 0;
//		motionChange_ = true;
//		moveAbleFlg_ = true;
//	}
//}

//
//	@brief	éÄñSâπçƒê∂
void SwordMan::DeadSound()
{
	Sound::getInstance().SE_play("S_DEAD");
}


//
//	@brief			ï`âÊ
void SwordMan::CharaRender()
{
	//ÉÇÉfÉãï`âÊ
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

	//UIï`âÊ
	UIRender();
}

////
////	@brief	ì¡éÍçUåÇìñÇΩÇËîªíË
//void SwordMan::Special_Attack_Collision()
//{
//	float atkRange = param_->attackRange_;
//	float atkDist = param_->attackReach_;
//	float backDist = param_->knockbackDist_;
//	float backSpeed = param_->knockbackSpeed_;
//	if (!aroundCharaList_.empty())
//	{
//		for (auto chara : aroundCharaList_)
//		{
//			if (collision_->CharaNear(m_Pos, chara->m_Pos, atkDist))
//			{
//				chara->SetKnockBack(m_Pos, backDist, backSpeed, charaType_);
//				if (chara->GetCharaType() == Enemy)
//				{
//					//ìGÇ…É_ÉÅÅ[ÉWÇ™ì¸Ç¡ÇΩéûÇÃSE
//					Sound::getInstance().SE_play("S_DAMAGE_HIT");
//					chara->DamageCalc(param_->specialAtk_);
//				}
//			}
//		}
//	}
//}