//
//	@file	JobManager.h
//	@brief	êEã∆ñàÇÃèàóù
//	@date	2016/11/10
//	@outher	êmâ»çÅïc

#include "JobManager.h"


JobManager::JobManager()
{
}

JobManager::~JobManager()
{
}

const char* JobManager::Read(const char* fileName)
{
	char FileName[80] = { 0 };
	//memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Player/");
	strcat_s(FileName, sizeof(FileName), fileName);

	return FileName;
}

void JobManager::CharaUpdate()
{
	
}

//////////////////////////////////////////////
void SwordMan::NormalAttack()
{
}

void SwordMan::SpecialAttack()
{
}

//////////////////////////////////////////////
void Witch::NormalAttack()
{
}

void Witch::SpecialAttack()
{
}

///////////////////////////////////////////////
void ShieldMan::NormalAttack()
{
}

void ShieldMan::SpecialAttack()
{
}

//////////////////////////////////////////////
void Bomber::NormalAttack()
{
}

void Bomber::SpecialAttack()
{
}