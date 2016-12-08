//
//	@file	Shield.h
//	@brief	‚mƒNƒ‰ƒX
//	@date	2016/11/21
//	@author	m‰È•c
//	@author	‹g‰z‘å‹R(ƒTƒEƒ“ƒh)

#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"

//	‚mƒNƒ‰ƒX
class ShieldMan :public JobManager
{
private:
	bool spMoveFlg_;
	D3DXVECTOR3 spMove_;
	void Attack_Collision(float hitAngle);
	//void Normal_Attack_Collision();
	//void Special_Attack_Collision();

	virtual void Normal_Attack();
	virtual void Special_Attack();
	virtual void Move(float speed);
	//virtual void Move_Update();
	virtual void DeadSound();
	virtual void DamegeSound() {};

public:
	ShieldMan(CharaType charaType);
	virtual ~ShieldMan();
	virtual void Reset();
	virtual void Attack();
	virtual void DamageCalc(unsigned int atk);					//ƒ_ƒ[ƒWŒvZ
};
