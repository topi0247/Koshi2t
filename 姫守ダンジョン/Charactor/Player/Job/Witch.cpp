#include "./Witch.h"


Witch::Witch(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	magicFlg_ = false;
	atkNo_ = noAtk;
	attackCount_ = 0;
}

Witch::~Witch()
{
}

//
//	@brief	UŒ‚
void Witch::Attack()
{
	if (atkNo_ == noAtk)
	{
		moveAbleFlg_ = true;
	}
	else
	{
		moveAbleFlg_ = false;
	}

	//atkNo_ = noAtk;
	if (magicFlg_ == false && GamePad::checkInput(charaType_, GamePad::InputName::A)
		/*|| GetKeyState('1') & 0x80*/)
	{
		++attackCount_;
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
		//hit = false;
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime =param_->chargeTime_;

	if (0 < attackCount_ && attackCount_ < inputTime)
	{
		atkNo_ = normalAtk;
	}
	else if (inputTime < attackCount_)
	{
		atkNo_ = charge;
	}

	if (atkNo_ == specialAtk)
	{
		Special_Attack();
	}

	if (magicFlg_ == true && !magicBall_.empty())
	{
		int count = 0;
		float kDist = 10;
		for (size_t i = 0; i < magicBall_.size(); i++)
		{
			magicBall_[i]->Move_Weapon(kDist);
			if (magicBall_[i]->GetDelFlg())
			{
				magicBall_.erase(magicBall_.begin() + count);
				atkNo_ = noAtk;
				--count;
			}
			++count;
		}
		if (magicBall_.empty())
		{
			magicBall_.clear();
			magicFlg_ = false;
		}
	}
}

//
//	@brief	’ÊíUŒ‚
void Witch::Normal_Attack()
{
	//float dist = param_->attackReach_;
	float kRange = param_->attackReach_;
	float kDist = param_->attackReach_;
	magicBallCount_ = 1;
	//if (magicFlg_)
	//{
	//	for (auto m : magicBall_)
	//	{
	//		m->Move_Weapon(dist);
	//	}
	//}
	if(!magicFlg_)
	{
		WeaponBall* magic= new WeaponBall(m_hWnd, m_pDevice, m_pDeviceContext, m_Pos);

		D3DXVECTOR3 vec(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);
		magic->SetDir(vec);
		magic->SetDamageList(allCharaList_, charaType_);
		magic->SetHitRangeKnockBackDist(kRange, kDist);
		magicBall_.push_back(magic);
		magicFlg_ = true;
	}
}

//
//	@brief	“ÁŽêUŒ‚
void Witch::Special_Attack()
{
	//float dist = param_->attackReach_;
	float kRange = param_->attackReach_+1;
	float kDist = param_->attackReach_;
	magicBallCount_ = 3;
	/*if (magicFlg_)
	{
		for (auto m : magicBall_)
		{
			m->Move_Weapon(dist);
		}
	}*/
	if(!magicFlg_)
	{
		float angle = D3DXToDegree(m_Yaw);
		for (int i = 0; i < magicBallCount_; i++)
		{
			WeaponBall* magic = new WeaponBall(m_hWnd, m_pDevice, m_pDeviceContext, m_Pos);
			int degree = 90 / (magicBallCount_ / 2 + 1);
			float temp = angle - 90 + degree + degree*i;
			temp = D3DXToRadian(temp);
			D3DXVECTOR3 vec(sinf(temp)*-0.1, 0, cosf(temp)*-0.1);
			magic->SetDir(vec);
			magic->SetScale(0.5);
			magic->SetDamageList(allCharaList_, charaType_);
			magic->SetHitRangeKnockBackDist(kRange, kDist);
			magicBall_.push_back(magic);
		}
		magicFlg_ = true;
	}
}

//
//	@brief	•`‰æ
void Witch::CharaRender(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	m_View = mView;
	m_Proj = mProj;
	Render();
	if (!magicBall_.empty())
	{
		for (auto m:magicBall_)
		{
			m->Render(mView, mProj);
		}
	}
}