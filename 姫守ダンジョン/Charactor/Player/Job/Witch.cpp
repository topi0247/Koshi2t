#include "./Witch.h"


Witch::Witch(Controller controller) :JobManager(controller)
{
	controller_ = controller;
	magicFlg_ = false;
	magicBall_ = nullptr;
}

//
//	@brief	çUåÇ
void Witch::Attack()
{
	//atkNo_ = noAtk;
	if (magicFlg_ == false && GamePad::checkInput(controller_, GamePad::InputName::A)
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

	if (magicFlg_ == true && magicBall_ != nullptr)
	{
		static int count = 0;
		for (int i = 0; i < magicBallCount_; i++)
		{
			if (magicBall_[i] != nullptr && magicBall_[i]->GetDelFlg())
			{
				delete magicBall_[i];
				magicBall_[i] = nullptr;
				atkNo_ = noAtk;
				++count;
			}
		}
		if (count == magicBallCount_)
		{
			delete[] magicBall_;
			magicBall_ = nullptr;
			magicFlg_ = false;
			count = 0;
		}
	}
}

//
//	@brief	í èÌçUåÇ
void Witch::Normal_Attack()
{
	float dist = 30;
	magicBallCount_ = 1;
	if (magicFlg_)
	{
		magicBall_[0]->Move_Weapon(dist);
	}
	else
	{
		magicBall_ = new WeaponBall*[magicBallCount_];
		magicBall_[0] = new WeaponBall(m_hWnd, m_pDevice, m_pDeviceContext, m_Pos);
		D3DXVECTOR3 vec(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);
		magicBall_[0]->SetDir(vec);
		magicFlg_ = true;
	}
}

//
//	@brief	ì¡éÍçUåÇ
void Witch::Special_Attack()
{
	float dist = 30;
	magicBallCount_ = 3;
	if (magicFlg_)
	{
		for (int i = 0; i < magicBallCount_; i++)
		{
			magicBall_[i]->Move_Weapon(dist);
		}
	}
	else
	{
		magicBall_ = new WeaponBall*[magicBallCount_];
		float angle = D3DXToDegree(m_Yaw);
		for (int i = 0; i < magicBallCount_; i++)
		{
			magicBall_[i] = new WeaponBall(m_hWnd, m_pDevice, m_pDeviceContext, m_Pos);
			int degree = 90 / (magicBallCount_ / 2 + 1);
			float temp = angle - 90 + degree + degree*i;
			temp = D3DXToRadian(temp);
			D3DXVECTOR3 vec(sinf(temp)*-0.1, 0, cosf(temp)*-0.1);
			magicBall_[i]->SetDir(vec);
			magicBall_[i]->SetScale(0.5);
		}
		magicFlg_ = true;
	}
}

//
//	@brief	ï`âÊ
void Witch::CharaRender(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	m_View = mView;
	m_Proj = mProj;
	Render();
	if (magicBall_ != nullptr)
	{
		for (int i = 0; i < magicBallCount_; i++)
		{
			if (magicBall_[i] != nullptr)
			{
				magicBall_[i]->Render(mView, mProj);
			}
		}
	}
}