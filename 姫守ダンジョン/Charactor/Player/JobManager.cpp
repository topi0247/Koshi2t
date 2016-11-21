//
//	@file	JobManager.h
//	@brief	êEã∆Ç≤Ç∆ÇÃèàóù
//	@date	2016/11/10
//	@outher	êmâ»çÅïc

#include "JobManager.h"

JobManager::JobManager(Controller controller, CharaType charatype)
	:timeCount_(0)
	//,mime_(player)
{
}

JobManager::~JobManager()
{
}


void JobManager::CharaUpdate()
{
	//çUåÇ
	Attack();
	/*if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		Attack();
	}*/

	//ïPåƒÇ—
	if (GamePad::checkInput(controller_, GamePad::InputName::B))
	{
		callFlg_ = true;
		//Princess_Call();
	}

	//ÉÇÅ[ÉVÉáÉìïœçX
	Motion_Update();

	//à⁄ìÆ
	float speed = 0.08;
	Move(speed);
}

////
////	@brief	ÉÇÅ[ÉVÉáÉìçXêV
//void JobManager::Motion_Update()
//{
//	m_pAnimController->AdvanceTime(0.001, NULL);
//
//	//çUåÇ
//	if (GamePad::checkInput(controller_, GamePad::InputName::A))
//	{
//		ChangeMotion(waitM);
//	}
//
//	//ïPåƒÇ—
//	if (GamePad::checkInput(controller_, GamePad::InputName::B))
//	{
//		ChangeMotion(walkM);
//	}
//}

//////////////////////////////////////////////
SwordMan::SwordMan(Controller controller, CharaType charatype) :JobManager(controller,charatype)
{
	controller_ = controller;
	charaType_ = charatype;
	col_ = new Collision();
}

//
//	@brief	çUåÇ
void SwordMan::Attack()
{
	if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		++attackCount_;
		atkNo_ = waitAtk;
	}
	else if (atkNo_ == specialAtk)
	{
		attackCount_ = 0;
		Special_Attack();

	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = 40;
	if (1 < attackCount_&& attackCount_ < inputTime)
	{
		atkNo_ = noAtk;
		Normal_Attack();
	}
	else if (inputTime < attackCount_)
	{
		atkNo_ = specialAtk;
	}
}

//
//	@breif	í èÌçUåÇ
void SwordMan::Normal_Attack()
{
	timeEnd_ = 10;
	if (++timeCount_ > timeEnd_)
	{
		atkNo_ = noAtk;
		attackCount_ = 0;
		timeCount_ = 0;
	}
}

//
//	@brief	í èÌçUåÇìñÇΩÇËîªíË
void SwordMan::Normal_Attack_Collision()
{
	if (aroundCharaList_[0] != nullptr)
	{
		for (auto chara : aroundCharaList_)
		{

		}
	}
}

//
//	@brief	ì¡éÍçUåÇ
void SwordMan::Special_Attack()
{
	//atkNo_ = noAtk;
}

//////////////////////////////////////////////
Witch::Witch(Controller controller, CharaType charatype) :JobManager(controller,charatype)
{
	controller_ = controller;
	charaType_ = charatype;
}

//
//	@brief	çUåÇ
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

void Witch::Normal_Attack()
{

}

void Witch::Special_Attack()
{
}

///////////////////////////////////////////////
ShieldMan::ShieldMan(Controller controller, CharaType charatype) :JobManager(controller,charatype)
{
	controller_ = controller;
	charaType_ = charatype;
}

//
//	@brief	çUåÇ
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
Bomber::Bomber(Controller controller, CharaType charatype) :JobManager(controller,charatype)
{
	controller_ = controller;
	charaType_ = charatype;
}

//
//	@brief	çUåÇ
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