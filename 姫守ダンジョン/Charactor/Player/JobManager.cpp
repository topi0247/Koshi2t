//
//	@file	JobManager.h
//	@brief	職業ごとの処理
//	@date	2016/11/10
//	@outher	仁科香苗

#include "JobManager.h"

JobManager::JobManager(Controller controller)
	:timeCount_(0)
	,hit(0)
{
}

JobManager::~JobManager()
{
}


void JobManager::CharaUpdate()
{
	//周辺にいるキャラチェック
	ArouncCharaCheck();

	//攻撃
	Attack();
	/*if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		Attack();
	}*/

	//姫呼び
	if (GamePad::checkInput(controller_, GamePad::InputName::B))
	{
		callFlg_ = true;
		//Princess_Call();
	}

	//モーション変更
	Motion_Update();

	//移動
	Move(0.1);
}

////
////	@brief	モーション更新
//void JobManager::Motion_Update()
//{
//	m_pAnimController->AdvanceTime(0.001, NULL);
//
//	//攻撃
//	if (GamePad::checkInput(controller_, GamePad::InputName::A))
//	{
//		ChangeMotion(waitM);
//	}
//
//	//姫呼び
//	if (GamePad::checkInput(controller_, GamePad::InputName::B))
//	{
//		ChangeMotion(walkM);
//	}
//}

//////////////////////////////////////////////
SwordMan::SwordMan(Controller controller) :JobManager(controller)
{
	controller_ = controller;
	col_ = new Collision();
}

//
//	@brief	攻撃
void SwordMan::Attack()
{
	if (GamePad::checkInput(controller_, GamePad::InputName::A)
		|| GetKeyState('1') & 0x80)
	{
		++attackCount_;
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

	unsigned int inputTime = 40;

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
//	@breif	通常攻撃
void SwordMan::Normal_Attack()
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
//	@brief	通常攻撃当たり判定
void SwordMan::Normal_Attack_Collision()
{
	float degree = D3DXToDegree(m_fYaw);

	if (!aroundCharaList_.empty())
	{
		for (auto chara : aroundCharaList_)
		{
			if (collision_->CharaNear(m_vPos, chara->m_vPos, 5))
			{
				D3DXVECTOR3 vec = chara->m_vPos - m_vPos;
				float angle = (atan2(vec.z, vec.x)*-1) - (D3DX_PI / 2.0f);
				angle = D3DXToDegree(angle);

				float hitAngle = 45;
				if (fabsf(degree - angle) <= 45)
				{
					hit = true;
					chara->SetKnockBackFlg();
					chara->SetKnockBackPos(m_vPos);
					chara->SetKnockBackDis(5);
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
//	@brief	特殊攻撃
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
//	@brief	特殊攻撃当たり判定
void SwordMan::Special_Attack_Collision()
{
	if (!aroundCharaList_.empty())
	{
		for (auto chara : aroundCharaList_)
		{
			if (collision_->CharaNear(m_vPos, chara->m_vPos, 5))
			{
				hit = true;
				chara->SetKnockBackFlg();
				chara->SetKnockBackPos(m_vPos);
				chara->SetKnockBackDis(5);
			}
		}
	}
}

//////////////////////////////////////////////
Witch::Witch(Controller controller) :JobManager(controller)
{
	controller_ = controller;
}

//
//	@brief	攻撃
void Witch::Attack()
{
	if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		++attackCount_;
		atkNo_ = waitAtk;
	}
	else if (atkNo_ != noAtk)
	{
		//unsigned int inputTime = playerParam_.chargeTime_;
		unsigned int inputTime = 40;
		if (1 < attackCount_&& attackCount_ < inputTime)
		{
			atkNo_ = normalAtk;
			Normal_Attack();
		}
		else if (inputTime < attackCount_)
		{
			atkNo_ = specialAtk;
			Special_Attack();
		}
	}
	else if (atkNo_ == noAtk)
	{
		attackCount_ = 0;
	}
	//char str[256];
	//sprintf(str, "A : %d", attackCount_);
	//debugText_->Render(str, 0, 10);
}

void Witch::Normal_Attack()
{

}

void Witch::Special_Attack()
{
}

///////////////////////////////////////////////
ShieldMan::ShieldMan(Controller controller) :JobManager(controller)
{
	controller_ = controller;
}

//
//	@brief	攻撃
void ShieldMan::Attack()
{
	if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		++attackCount_;
		atkNo_ = waitAtk;
	}
	else if (atkNo_ != noAtk)
	{
		//unsigned int inputTime = playerParam_.chargeTime_;
		unsigned int inputTime = 40;
		if (1 < attackCount_&& attackCount_ < inputTime)
		{
			atkNo_ = normalAtk,
				Normal_Attack();
		}
		else if (inputTime < attackCount_)
		{
			atkNo_ = specialAtk;
			Special_Attack();
		}
	}
	else if (atkNo_ == noAtk)
	{
		attackCount_ = 0;
	}
	//char str[256];
	//sprintf(str, "A : %d", attackCount_);
	//debugText_->Render(str, 0, 10);
}

void ShieldMan::Normal_Attack()
{
}

void ShieldMan::Special_Attack()
{
}

//////////////////////////////////////////////
Bomber::Bomber(Controller controller) :JobManager(controller)
{
	controller_ = controller;
}

//
//	@brief	攻撃
void Bomber::Attack()
{
	if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		++attackCount_;
		atkNo_ = waitAtk;
	}
	else if (atkNo_ != noAtk)
	{
		//unsigned int inputTime = playerParam_.chargeTime_;
		unsigned int inputTime = 40;
		if (1 < attackCount_&& attackCount_ < inputTime)
		{
			atkNo_ = normalAtk,
				Normal_Attack();
		}
		else if (inputTime < attackCount_)
		{
			atkNo_ = specialAtk;
			Special_Attack();
		}
	}
	else if (atkNo_ == noAtk)
	{
		attackCount_ = 0;
	}
	//char str[256];
	//sprintf(str, "A : %d", attackCount_);
	//debugText_->Render(str, 0, 10);
}

void Bomber::Normal_Attack()
{
}

void Bomber::Special_Attack()
{
}