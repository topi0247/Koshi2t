//
//	@file	JobManager.h
//	@brief	E‹Æ‚²‚Æ‚Ìˆ—
//	@date	2016/11/10
//	@outher	m‰È•c

#include "JobManager.h"

JobManager::JobManager(Controller controller)
	:timeCount_(0)
{
}

JobManager::~JobManager()
{
}


void JobManager::CharaUpdate()
{
	//UŒ‚
	Attack();
	/*if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		Attack();
	}*/
	
	//•PŒÄ‚Ñ
	if (GamePad::checkInput(controller_, GamePad::InputName::B))
	{
		callFlg_ = true;
		//Princess_Call();
	}

	//ƒ‚[ƒVƒ‡ƒ“•ÏX
	Motion_Update();

	//ˆÚ“®

	Move(0.1);

}

////
////	@brief	ƒ‚[ƒVƒ‡ƒ“XV
//void JobManager::Motion_Update()
//{
//	m_pAnimController->AdvanceTime(0.001, NULL);
//
//	//UŒ‚
//	if (GamePad::checkInput(controller_, GamePad::InputName::A))
//	{
//		ChangeMotion(waitM);
//	}
//
//	//•PŒÄ‚Ñ
//	if (GamePad::checkInput(controller_, GamePad::InputName::B))
//	{
//		ChangeMotion(walkM);
//	}
//}

//////////////////////////////////////////////
SwordMan::SwordMan(Controller controller):JobManager(controller)
{
	controller_ = controller;
	col_ = new Collision();
}

void SwordMan::Normal_Attack()
{
	timeEnd_ = 10;
	if (++timeCount_>timeEnd_)
	{
		atkNo_ = noAtk;
		timeCount_ = 0;
	}
}

void SwordMan::Special_Attack()
{
	atkNo_ = noAtk;
}

//////////////////////////////////////////////
Witch::Witch(Controller controller):JobManager(controller)
{
	controller_ = controller;
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
void Bomber::Normal_Attack()
{
}

void Bomber::Special_Attack()
{
}