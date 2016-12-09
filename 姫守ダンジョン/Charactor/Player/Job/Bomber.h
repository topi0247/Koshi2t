//
//	@file	Bomber.h
//	@brief	爆弾士クラス
//	@date	2016/11/21
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"

//	爆弾士クラス
class Bomber :public JobManager
{
private:
	WeaponBall* bomb_;

	bool bombFlg_;	//爆弾が発動中かどうか
	bool invinsibleFlg_;	//無敵中かどうか
	int invisibleCount_;
	int bombCount_;
	float bombScale_;
	//WeaponBall** bomb_;
	std::vector<WeaponBall*> bombList_;

	virtual void WeaponUpdate();
	virtual void Normal_Attack();
	virtual void Special_Attack();
	virtual void MoveCharaHit();
	virtual void DeadSound();
	virtual void Move(float speed);
	virtual void DamegeSound() {};
public:
	Bomber(CharaType charaType);
	virtual ~Bomber();
	virtual const char* CharaInit(const char* fileName);
	virtual void Reset();
	virtual void Attack();
	//virtual void Move_Update();
	virtual void DamageCalc(unsigned int atk);					//ダメージ計算
	virtual void CharaRender();
};