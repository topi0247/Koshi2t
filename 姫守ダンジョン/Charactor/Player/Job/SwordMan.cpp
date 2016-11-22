#include "./SwordMan.h"


SwordMan::SwordMan(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;

}

SwordMan::~SwordMan()
{

}

//
//	@brief	UŒ‚
void SwordMan::Attack()
{
	if (atkNo_ == noAtk)
	{
		moveAbleFlg_ = true;
	}
	else
	{
		moveAbleFlg_ = false;
	}

	if (GamePad::checkInput(charaType_,GamePad::InputName::A)
		/*|| GetKeyState('1') & 0x80*/)
	{
		++attackCount_;
		atkNo_ = waitAtk;
	}
	else if (atkNo_ == normalAtk)
	{
		attackCount_ = 0;
		//atkNo_ = noAtk;
		//Normal_Attack();
		//hit = false;
		//atkNo_ = noAtk;
		//Special_Attack();
	}
	else if (atkNo_ == charge)
	{
		attackCount_ = 0;
		atkNo_ = specialAtk;
		hit = false;
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = param_->chargeTime_;

	if (0 < attackCount_ && attackCount_ < inputTime)
	{
		atkNo_ = normalAtk;
	}
	else if (inputTime < attackCount_)
	{
		atkNo_ = charge;
	}

	if (atkNo_ == normalAtk)
	{
		Normal_Attack();
	}
	else if (atkNo_ == specialAtk)
	{
		Special_Attack();
	}
}

//
//	@breif	’ÊíUŒ‚
void SwordMan::Normal_Attack()
{
	Normal_Attack_Collision();
	timeEnd_ = 40;
	if (++timeCount_ > timeEnd_)
	{
		atkNo_ = noAtk;
		//attackCount_ = 0;
		timeCount_ = 0;
		hit = false;
	}
}

//
//	@brief	’ÊíUŒ‚“–‚½‚è”»’è
void SwordMan::Normal_Attack_Collision()
{
	float degree = D3DXToDegree(m_Yaw);
	float atkDist = param_->attackReach_;
	float hitAngle = param_->attackRange_;
	float backDist = param_->attackReach_;

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
					chara->SetKnockBack(m_Pos, backDist);
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
void SwordMan::Special_Attack()
{
	Special_Attack_Collision();
	timeEnd_ = 30;
	if (++timeCount_ > timeEnd_)
	{
		atkNo_ = noAtk;
		//attackCount_ = 0;
		timeCount_ = 0;
		hit = false;
	}
}

//
//	@brief	“ÁŽêUŒ‚“–‚½‚è”»’è
void SwordMan::Special_Attack_Collision()
{
	float atkRange = param_->attackRange_;
	float atkDist = param_->attackReach_;
	float backDist = param_->attackReach_;
	if (!aroundCharaList_.empty())
	{
		for (auto chara : aroundCharaList_)
		{
			if (collision_->CharaNear(m_Pos, chara->m_Pos, atkDist))
			{
				hit = true;
				chara->SetKnockBack(m_Pos, backDist);
			}
		}
	}
}