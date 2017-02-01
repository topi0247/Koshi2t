//
//	@file	Witch.h
//	@brief	–‚“±mƒNƒ‰ƒX
//	@date	2016/11/21
//	@author	m‰È•c
//	@author	‹g‰z‘å‹R(ƒTƒEƒ“ƒh)

#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"
#include "./../Job/WeaponBall.h"
#include "../../../UI/TD_Graphics.h"

//	–‚“±mƒNƒ‰ƒX
class Witch :public JobManager
{
private:

	bool magicFlg_;	//‹Z‚ª”­“®’†‚©‚Ç‚¤‚©
	int magicBallCount_;
	float magicSpeed_;
	CD3DXMESH* magic_;
	WeaponBall* magicBall_;

	void InstanceMagicBall(float range,float atk,bool flg);
	//void RazorBeam();
	virtual void WeaponUpdate();
	virtual void Normal_Attack();
	virtual void Special_Attack();
	virtual void DeadSound();
	virtual void DamageSound();

	//map<string, TD_Graphics*> Witch_UI;

public:
	Witch(CharaType charaType);
	virtual ~Witch();
	//virtual const char* CharaInit(const char* fileName);
	virtual void Reset();
	virtual void Attack();
	virtual void CharaRender();
};