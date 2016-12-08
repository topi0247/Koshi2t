//
//	@file	SwordMan.h
//	@brief	Œ•mƒNƒ‰ƒX
//	@date	2016/11/21
//	@author	m‰È•c
//	@author	‹g‰z‘å‹R(ƒTƒEƒ“ƒh)

#pragma once
#include "./../../../Origin.h"
#include "./../../Player/JobManager.h"

//	Œ•mƒNƒ‰ƒX
class SwordMan :public JobManager
{
private:
	void Normal_Attack_Collision();
	void Special_Attack_Collision();
	virtual void Normal_Attack();
	virtual void Special_Attack();
	virtual void DeadSound();
	virtual void DamageSound();
public:
	SwordMan(CharaType charaType);
	virtual ~SwordMan();
	virtual void Reset();
	virtual void Attack();
};