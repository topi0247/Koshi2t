#include "ShieldMan.h"

ShieldMan::ShieldMan(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	m_Pitch = D3DXToRadian(90);
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
		attackCount_ = 0;
		atkNo_ = noAtk;
		hit = false;
		spMove_ = D3DXVECTOR3(1, 0, 1);
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = param_->chargeTime_;

	if (0 < attackCount_ && attackCount_ < inputTime)
	{
		atkNo_ = normalAtk;
	}
	else if (inputTime < attackCount_)
	{
		atkNo_ = specialAtk;
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
//	@brief	’ÊíUŒ‚“–‚½‚è”»’è
void ShieldMan::Normal_Attack_Collision()
{
	float degree = D3DXToDegree(m_Yaw);
	float hitAngle = param_->attackRange_;
	float atkDist = param_->attackReach_;
	float backDist = param_->attackReach_;

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
void ShieldMan::Special_Attack()
{
	spMove_ = D3DXVECTOR3(param_->specialMoveSpeed_, param_->specialMoveSpeed_, param_->specialMoveSpeed_);
	Special_Attack_Collision();
}

//
//	@brief	“ÁŽêUŒ‚“–‚½‚è”»’è
void ShieldMan::Special_Attack_Collision()
{
	float degree = D3DXToDegree(m_Yaw);
	float hitAngle = param_->attackRange_;
	float atkDist = param_->attackReach_;
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
//	@breif	‚Žm—pˆÚ“®ˆ—
void ShieldMan::Move_Update()
{
	if (knockBackFlg_ == false && atkNo_ ==(!normalAtk || !specialAtk))
	{
		m_Pos += m_Dir;
	}
	else if(knockBackFlg_==true && atkNo_!=specialAtk)
	{
		KnockBack(knockBackPos_, knockBackDis_);
	}
	else if (atkNo_ == specialAtk)
	{
		float sp = param_->specialMoveSpeed_;
		m_Pos += D3DXVECTOR3(m_Dir.x*sp, 0, m_Dir.z*sp);
	}
}