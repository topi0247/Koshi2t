//
//	@file	EnemyJobManager.h
//	@brief	“G‚²‚Æ‚Ìˆ—
//	@date	2016/11/13
//	@author	‹g‰z‘å‹R
//	@author	m‰È•c

#pragma once
#include "./../Enemy/EnemyManager.h"


//	E‹ÆŠÇ—ƒNƒ‰ƒX
class EnemyJobManager :public EnemyManager
{
protected:

public:
	EnemyJobManager();
	virtual ~EnemyJobManager();
	virtual void Reset();
	virtual void CharaUpdate();
};

//	ƒXƒ‰ƒCƒ€ƒNƒ‰ƒX
class Slim :public EnemyJobManager
{
private:
	virtual void NormalAttack();
public:
	//Slim() {};
	virtual ~Slim() {};
};

//	ƒSƒuƒŠƒ“ƒNƒ‰ƒX
class Goblin :public EnemyJobManager
{
private:
	virtual void NormalAttack();
public:
	virtual ~Goblin() {};
};


#include "./../Player/Job/WeaponBall.h"
//	ƒXƒPƒ‹ƒgƒ“ƒNƒ‰ƒX
class Skeleton :public EnemyJobManager
{
private:
	virtual void NormalAttack();
	std::vector<WeaponBall*> atkList_;
public:
	virtual ~Skeleton() {};
	virtual void Reset();
	virtual void CharaRender();		//•`‰æ

};