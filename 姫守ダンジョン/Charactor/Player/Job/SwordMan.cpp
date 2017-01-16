//
//	@file	SwordMan.cpp
//	@brief	剣士クラス
//	@date	2016/11/21
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#include "./SwordMan.h"


SwordMan::SwordMan(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
}

SwordMan::~SwordMan()
{

}


//
//	@brief	リセット
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

	m_Pos = D3DXVECTOR3(-2.25 + charaType_*1.5, 0, -10);
}


//
//	@brief	攻撃
void SwordMan::Attack()
{
	if (GamePad::checkInput(charaType_, GamePad::InputName::A)
		/*|| GetKeyState('1') & 0x80*/)
	{
		++attackCount_;
		atkNo_ = waitAtk;
		moveAbleFlg_ = false;
	}
	else if (atkNo_ == normalAtk)
	{
		attackCount_ = 0;
		//motionCount_ = 0;
		//atkNo_ = noAtk;
		//Normal_Attack();
		//hit = false;
		//atkNo_ = noAtk;
		//Special_Attack();
	}
	else if (atkNo_ == charge)
	{
		attackCount_ = 0;
		motionCount_ = 0;
		motionChange_ = true;
		atkNo_ = specialAtk;
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	/* 修正の必要あり */
	unsigned int inputTime = motionSpeed_;

	if (0 < attackCount_ && attackCount_ <= inputTime)
	{
		atkNo_ = normalAtk;
	}
	//else if (inputTime < attackCount_)
	//{
	//	atkNo_ = charge;
	//	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("charge")->id_)
	//	{
	//		motionChange_ = false;
	//		//motionNo_ = motion_->GetMotion("charge")->id_;
	//		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
	//		//timeEnd_ = motion_->GetMotion("charge")->frame_;
	//		//motionSpeed_ = 1 / (float)timeEnd_;
	//		ChangeMotion(motion_, "charge");
	//	}
	//}

	if (atkNo_ == normalAtk)
	{
		Normal_Attack();
	}
	/*else if (atkNo_ == specialAtk)
	{
		Special_Attack();
	}*/
}

//
//	@breif	通常攻撃
void SwordMan::Normal_Attack()
{
	if (motionChange_ == true && motionNo_ != motion_->GetMotion("attack1")->id_)
	{
		Sound::getInstance().SE_play("S_NORMALATK");

		motionChange_ = false;
		ChangeMotion(motion_, "attack1");


		Normal_Attack_Collision();

	}

	if (++motionCount_ > motionFrame_)
	{
		atkNo_ = noAtk;
		//attackCount_ = 0;
		motionCount_ = 0;
		motionChange_ = true;
		moveAbleFlg_ = true;
	}
}

//
//	@brief	通常攻撃当たり判定
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
						//敵にダメージが入った時のSE
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

//
//	@brief	特殊攻撃
void SwordMan::Special_Attack()
{
	Special_Attack_Collision();

	if (motionChange_ == true && motionNo_ != motion_->GetMotion("special")->id_)
	{
		Sound::getInstance().SE_play("S_SPECIAL");

		motionChange_ = false;
		//motionNo_ = motion_->GetMotion("special")->id_;
		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//timeEnd_ = motion_->GetMotion("special")->frame_;
		//motionSpeed_ = 1 / (float)timeEnd_;
		ChangeMotion(motion_, "special");
	}

	if (++motionCount_ > motionFrame_)
	{
		atkNo_ = noAtk;
		//attackCount_ = 0;
		motionCount_ = 0;
		motionChange_ = true;
		moveAbleFlg_ = true;
	}
}

//
//	@brief	死亡音再生
void SwordMan::DeadSound()
{
	Sound::getInstance().SE_play("S_DEAD");
}

//
//	@brief	特殊攻撃当たり判定
void SwordMan::Special_Attack_Collision()
{
	float atkRange = param_->attackRange_;
	float atkDist = param_->attackReach_;
	float backDist = param_->knockbackDist_;
	float backSpeed = param_->knockbackSpeed_;
	if (!aroundCharaList_.empty())
	{
		for (auto chara : aroundCharaList_)
		{
			if (collision_->CharaNear(m_Pos, chara->m_Pos, atkDist))
			{
				chara->SetKnockBack(m_Pos, backDist, backSpeed, charaType_);
				if (chara->GetCharaType() == Enemy)
				{
					//敵にダメージが入った時のSE
					Sound::getInstance().SE_play("S_DAMAGE_HIT");
					chara->DamageCalc(param_->specialAtk_);
				}
			}
		}
	}
}