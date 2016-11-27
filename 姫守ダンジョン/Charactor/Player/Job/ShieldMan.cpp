#include "ShieldMan.h"

ShieldMan::ShieldMan(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	spMoveFlg_ = false;
}

ShieldMan::~ShieldMan()
{

}

//
//	@brief	UŒ‚
void ShieldMan::Attack()
{
	if (GamePad::checkInput(charaType_, GamePad::InputName::A)
		/*|| GetKeyState('1') & 0x80*/)
	{
		++attackCount_;
	}
	else if (atkNo_ == normalAtk)
	{
		attackCount_ = 0;
		//atkNo_ = noAtk;
		Normal_Attack();
		//hit = false;
		//atkNo_ = noAtk;
		//Special_Attack();
	}
	else
	{
		spMoveFlg_ = false;
		attackCount_ = 0;
		atkNo_ = noAtk;
		hit = false;
		spMove_ = D3DXVECTOR3(1, 0, 1);
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = FPS*param_->chargeTime_;

	if (0 < attackCount_ && attackCount_ <= inputTime)
	{
		atkNo_ = normalAtk;
	}
	else if (inputTime < attackCount_ && attackCount_- inputTime< motion_->GetMotion("special")->frame_)
	{
		atkNo_ = specialAtk;
	}
	else
	{
		spMoveFlg_ = true;
	}
	
	if (atkNo_ == specialAtk)
	{
		Special_Attack();
	}
}

//
//	@brief	’ÊíUŒ‚
void ShieldMan::Normal_Attack()
{
	Normal_Attack_Collision();
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("attack1")->id_)
	{
		motionChange_ = false;
		motionNo_ = motion_->GetMotion("attack1")->id_;
		m_pD3dxMesh->ChangeAnimSet(motionNo_);
		timeEnd_ = motion_->GetMotion("attack1")->frame_;
		motionSpeed_ = 1 / (float)timeEnd_;
		motionCount_ = 0;
	}

	if (++motionCount_ > timeEnd_)
	{
		atkNo_ = noAtk;
		//attackCount_ = 0;
		motionChange_ = true;
		motionCount_ = 0;
		hit = false;
	}
}

//
//	@brief	’ÊíUŒ‚“–‚½‚è”»’è
void ShieldMan::Normal_Attack_Collision()
{
	float degree = D3DXToDegree(m_Yaw);
	float hitAngle = param_->attackRange_;
	float atkDist = param_->attackReach_;
	float backDist = param_->knockbackDist_;
	float backSpeed = param_->knockbackSpeed_;

	if (!aroundCharaList_.empty())
	{
		for (auto chara : aroundCharaList_)
		{
			if (collision_->CharaNear(m_Pos, chara->m_Pos, atkDist))
			{
				D3DXVECTOR3 vec = chara->m_Pos - m_Pos;
				float angle = (atan2(vec.z, vec.x)*-1) - (D3DX_PI / 2.0f);
				angle = D3DXToDegree(angle);

				if (fabsf(degree - angle) <= hitAngle)
				{
					hit = true;
					chara->SetKnockBack(m_Pos, backDist,backSpeed);
					if (chara->GetCharaType() == Enemy)
					{
						chara->DamageCalc(param_->normalAtk_);
					}
				}
				else
				{
					hit = false;
				}
			}
		}
	}
}

//
//	@brief	“ÁŽêUŒ‚
void ShieldMan::Special_Attack()
{
	//spMove_ = D3DXVECTOR3(param_->specialMoveSpeed_, param_->specialMoveSpeed_, param_->specialMoveSpeed_);
	Special_Attack_Collision();
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("special")->id_)
	{
		motionChange_ = false;
		motionNo_ = motion_->GetMotion("special")->id_;
		m_pD3dxMesh->ChangeAnimSet(motionNo_);
		timeEnd_ = motion_->GetMotion("special")->frame_;
		motionSpeed_ = 1 / (float)timeEnd_;
		motionCount_ = 0;
	}

	if (++motionCount_ > timeEnd_)
	{
		atkNo_ = noAtk;
		//attackCount_ = 0;
		motionChange_ = true;
		motionCount_ = 0;
		hit = false;
	}

}

//
//	@brief	“ÁŽêUŒ‚“–‚½‚è”»’è
void ShieldMan::Special_Attack_Collision()
{
	float degree = D3DXToDegree(m_Yaw);
	float hitAngle = param_->attackRange_;
	float atkDist = param_->attackReach_;
	float backDist = param_->knockbackDist_;

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
					hit = true;
					if (chara->GetCharaType() == Enemy)
					{
						chara->DamageCalc(param_->specialAtk_);
					}
				}
				else
				{
					hit = false;
				}
			}
		}
	}
}

//
//	@brief	ƒ_ƒ[ƒWŒvŽZ
void ShieldMan::DamageCalc(unsigned int atk)
{
	float damage = 0;
	float constant = 1;
	if (atkNo_ != specialAtk)
	{
		damage = atk / (1 + ((float)param_->def_ / 100));
	}
	else
	{
		damage = constant;
	}

	hp_ -= damage;
	if (hp_ <= 0)
	{
		hp_ = 0;
		aliveFlg_ = false;
	}

}

//
//	@breif	‚Žm—pˆÚ“®ˆ—
void ShieldMan::Move_Update()
{
	float backSpeed = param_->knockbackSpeed_;

	if (aliveFlg_ == true)
	{
		if (knockBackFlg_ == false && atkNo_ == (!normalAtk || !specialAtk))
		{
			m_Pos += m_Dir;
			if (motionChange_ == true && motionNo_ != motion_->GetMotion("walk")->id_)
			{
				motionNo_ = motion_->GetMotion("walk")->id_;
				m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("walk")->id_);
				//ƒ‚[ƒVƒ‡ƒ“‘¬“x
				motionSpeed_ = 1 / (float)motion_->GetMotion("walk")->frame_;
			}
		}
		else if (knockBackFlg_ == true && atkNo_ != specialAtk)
		{
			KnockBack(knockBackPos_, knockBackDis_,backSpeed);
		}
		else if (atkNo_ == specialAtk)
		{
			float sp = param_->specialMoveSpeed_;
			m_Pos += D3DXVECTOR3(m_Dir.x*sp, 0, m_Dir.z*sp);
			if (motionChange_ == true && motionNo_ != motion_->GetMotion("specialWalk")->id_)
			{
				motionNo_ = motion_->GetMotion("specialWalk")->id_;
				m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("specialWalk")->id_);
				//ƒ‚[ƒVƒ‡ƒ“‘¬“x
				motionSpeed_ = 1 / (float)motion_->GetMotion("specialWalk")->frame_;
			}
		}
	}
}