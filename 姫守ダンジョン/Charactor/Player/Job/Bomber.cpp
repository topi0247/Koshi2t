#include "./Bomber.h"

Bomber::Bomber(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	bombFlg_ = false;
	bomb_.clear();
	bombScale_ = 1;
	bombCount_ = 1;
}

Bomber::~Bomber()
{

}

//
//	@brief	UŒ‚
void Bomber::Attack()
{
	if (GamePad::checkInput(charaType_, GamePad::InputName::A)
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

	unsigned int inputTime = param_->chargeTime_;

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

	if (!bomb_.empty())
	{
		bombFlg_ = true;
		//static int count = 0;
		//int count = 0;
		for (auto b : bomb_)
		{
			int frame = FPS*1.5;
			b->Time_Del_Weapon(frame);
		}
		if (/*b != nullptr &&*/ bomb_[0]->GetDelFlg())
		{
			bomb_.erase(bomb_.begin());

			//delete b;
			//b = nullptr;
			//++count;
			//--count;
		}
		//++count;
		if (bomb_.empty())
		{
			bomb_.clear();
			bombFlg_= false;
			//count = 0;
		}

		/*if (count == bombCount_)
		{
		bomb_.clear();
		bombFlg_ = false;
		count = 0;
		}*/
	}
}

//
//	@brief	’ÊíUŒ‚
void Bomber::Normal_Attack()
{
	size_t size = 2;
	float range = param_->attackRange_;
	float dist = param_->attackReach_;
	if (bomb_.empty() || bomb_.size() < size)
	{
		WeaponBall* bomb = new WeaponBall(m_hWnd, m_pDevice, m_pDeviceContext, m_Pos);
		bomb->SetDamageList(allCharaList_, charaType_);
		bomb->SetHitRangeKnockBackDist(range, dist);
		bomb_.push_back(bomb);
	}
	atkNo_ = noAtk;
}

//
//	@brief	“ÁŽêUŒ‚
void Bomber::Special_Attack()
{
	if (++timeCount_ % (FPS * 3) == 0)
	{
		atkNo_ = noAtk;
		timeCount_ = 0;
	}
}

//
//	@brief	”š’eŽm—pˆÚ“®ˆ—
void Bomber::Move_Update()
{
	if (aliveFlg_ == true)
	{
		if (knockBackFlg_ == false && atkNo_ != normalAtk)
		{
			m_Pos += m_Dir;
		}
		else if (knockBackFlg_ == true && atkNo_ != specialAtk)
		{
			KnockBack(knockBackPos_, knockBackDis_);
		}
	}
}

//
//	@brief	•`‰æ
void Bomber::CharaRender(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	m_View = mView;
	m_Proj = mProj;
	Render();
	if (!bomb_.empty())
	{
		for (auto b : bomb_)
		{
			if (b != nullptr)
			{
				b->Render(mView, mProj);
			}
		}
	}
}