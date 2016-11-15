//
//	@file	JobManager.h
//	@brief	�E�Ƃ��Ƃ̏���
//	@date	2016/11/10
//	@outher	�m�ȍ��c

#include "JobManager.h"

JobManager::JobManager(Controller controller)
{
}

JobManager::~JobManager()
{
}


void JobManager::CharaUpdate()
{
	Move(0.05);
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