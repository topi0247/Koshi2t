//
//	@file	JobManager.h
//	@brief	E‹Æ–ˆ‚Ìˆ—
//	@date	2016/11/10
//	@outher	m‰È•c

#pragma once
#include "./../Player/PlayerManager.h"

//	ƒpƒ‰ƒ[ƒ^
struct Parameter
{
	unsigned char name_[30];	//E‹Æ–¼
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//’ÊíUŒ‚—Í
	unsigned int specialAtk_;	//“ÁêUŒ‚—Í
	unsigned int def_;			//ç”õ—Í
	unsigned int waitTime_;		//‘Ò‹@ŠÔ
	float speed_;				//ˆÚ“®‘¬“x
	float weight_;				//d‚³
};

//	E‹ÆŠÇ—ƒNƒ‰ƒX
class JobManager :public PlayerManager
{
	virtual const char* Read(const char* fileName);	//“Ç‚İ‚İ
public:
	JobManager();
	virtual ~JobManager();
	virtual void CharaUpdate();
};

//	Œ•mƒNƒ‰ƒX
class SwordMan :public JobManager
{
protected:
	virtual void NormalAttack();
	virtual void SpecialAttack();
public:
};

//	–‚“±mƒNƒ‰ƒX
class Witch :public JobManager
{
protected:
	virtual void NormalAttack();
	virtual void SpecialAttack();
public:
};

//	‚mƒNƒ‰ƒX
class ShieldMan :public JobManager
{
protected:
	virtual void NormalAttack();
	virtual void SpecialAttack();
public:
};

//	”š’emƒNƒ‰ƒX
class Bomber :public JobManager
{
protected:
	virtual void NormalAttack();
	virtual void SpecialAttack();
public:
};