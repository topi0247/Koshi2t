#include "./Bomber.h"

Bomber::Bomber(Controller controller) :JobManager(controller)
{
	controller_ = controller;
	bombFlg_ = false;
	bomb_.clear();
	bombScale_ = 1;
	bombCount_ = 1;
}

//
//	@brief	UŒ‚
void Bomber::Attack()
{
	if (GamePad::checkInput(controller_, GamePad::InputName::A)
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

	unsigned int inputTime = 40;

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
	if (bomb_.empty() || bomb_.size() < size)
	{
		WeaponBall* bomb = new WeaponBall(m_hWnd, m_pDevice, m_pDeviceContext, m_Pos);
		bomb_.push_back(bomb);
		bomb->SetDamageList(aroundCharaList_);
	}
	atkNo_ = noAtk;
}

//
//	@brief	“ÁêUŒ‚
void Bomber::Special_Attack()
{
	atkNo_ = noAtk;
}

//
//	@brief	”í’e‚·‚éƒLƒƒƒ‰ƒŠƒXƒg‚ÌƒZƒbƒg
void Bomber::SetForBombCharaList(std::vector<CharactorManager*> list)
{
	if (!bomb_.empty())
	{
		for (auto c : list)
		{
			for (auto b : bomb_)
			{
				if (collision_->CharaNear(b->GetPosition(), c->m_Pos, b->GetHitRange()))
				{
					b->SetDamageChara(c);
				}
			}
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