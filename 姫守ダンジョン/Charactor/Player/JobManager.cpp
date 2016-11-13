//
//	@file	JobManager.h
//	@brief	E‹Æ‚²‚Æ‚Ìˆ—
//	@date	2016/11/10
//	@outher	m‰È•c

#include "JobManager.h"

JobManager::JobManager(Controller controller)
{
}

JobManager::~JobManager()
{
}


void JobManager::CharaUpdate()
{
	Motion_Update();
	Move(0.05);
}

void JobManager::Motion_Update()
{
	m_pAnimController->AdvanceTime(0.001, NULL);

	if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		ChangeMotion(walkM);
		//motionNo_ = waitM;
	}

	if (GamePad::checkInput(controller_, GamePad::InputName::B))
	{
		ChangeMotion(waitM);
		//motionNo_ = walkM;
	}
	//ChangeMotion(motionNo_);
}

//////////////////////////////////////////////
SwordMan::SwordMan(Controller controller):JobManager(controller)
{
	controller_ = controller;
}

void SwordMan::NormalAttack()
{
}

void SwordMan::SpecialAttack()
{
}

//////////////////////////////////////////////
Witch::Witch(Controller controller):JobManager(controller)
{
	controller_ = controller;
}

void Witch::NormalAttack()
{
}

void Witch::SpecialAttack()
{
}

///////////////////////////////////////////////
ShieldMan::ShieldMan(Controller controller) :JobManager(controller)
{
	controller_ = controller;
}

void ShieldMan::NormalAttack()
{
}

void ShieldMan::SpecialAttack()
{
}

//////////////////////////////////////////////
Bomber::Bomber(Controller controller) :JobManager(controller)
{
	controller_ = controller;
}
void Bomber::NormalAttack()
{
}

void Bomber::SpecialAttack()
{
}