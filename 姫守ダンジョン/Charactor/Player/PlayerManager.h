//
//	@file	PlayerManager.h
//	@brief	ƒvƒŒƒCƒ„[ŠÇ—ƒNƒ‰ƒX
//	@date	2016/11/09
//	@outher	m‰È•c
#pragma once
#include "./../CharactorManager.h"
#include "./GamePad.h"

class PlayerManager : public CharactorManager
{
protected:
	enum Controller
	{
		player1=0,
		player2,
		player3,
		player4,
	};
	Controller controller_;

	virtual void NormalAttack() = 0;	//’ÊíUŒ‚
	virtual void SpecialAttack() = 0;	//“ÁêUŒ‚
	virtual void Attack();				//UŒ‚
	virtual void Move(float speed);		//ˆÚ“®ˆ—
	virtual void Dead();				//€–S
	virtual void Motion_Update() {};	//ƒ‚[ƒVƒ‡ƒ“XV
	void Queen_Lite();					//•P‚¿ã‚°
	void Revival();						//•œŠˆ
public:
	PlayerManager();
	virtual ~PlayerManager() {};
};