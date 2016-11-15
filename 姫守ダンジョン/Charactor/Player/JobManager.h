//
//	@file	JobManager.h
//	@brief	E‹Æ–ˆ‚Ìˆ—
//	@date	2016/11/10
//	@outher	m‰È•c

#pragma once
#include "./../Player/PlayerManager.h"
#include "./../../Read/ParameterRead.h"

//	ƒpƒ‰ƒ[ƒ^
struct PlayerParameter
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
	//void Motion_Update();
public:
	JobManager(Controller controller);
	virtual ~JobManager();
	virtual void CharaUpdate();
};

//	Œ•mƒNƒ‰ƒX
class SwordMan :public JobManager
{
protected:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	SwordMan(Controller controller);
};

//	–‚“±mƒNƒ‰ƒX
class Witch :public JobManager
{
protected:	
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Witch(Controller controller);
};

//	‚mƒNƒ‰ƒX
class ShieldMan :public JobManager
{
protected:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	ShieldMan(Controller controller);
};

//	”š’emƒNƒ‰ƒX
class Bomber :public JobManager
{
private:

protected:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Bomber(Controller controller);
};