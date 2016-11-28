#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"
#include "./../Job/WeaponBall.h"

//	–‚“±ŽmƒNƒ‰ƒX
class Witch :public JobManager
{
	bool magicFlg_;	//‹Z‚ª”­“®’†‚©‚Ç‚¤‚©
	int magicBallCount_;
	WeaponBall* magic_;
	std::vector<WeaponBall*> magicBall_;
private:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Witch(CharaType charaType);
	virtual ~Witch();
	virtual const char* CharaInit(const char* fileName);
	virtual void Attack();
	virtual void CharaRender();
};