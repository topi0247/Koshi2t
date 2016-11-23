//
//	@file	JobManager.h
//	@brief	“G‚²‚Æ‚Ìˆ—
//	@date	2016/11/13
//	@outher	‹g‰z‘å‹R

#pragma once
#include "./../Enemy/EnemyManager.h"


//	E‹ÆŠÇ—ƒNƒ‰ƒX
class EnemyJobManager :public EnemyManager
{
public:
	EnemyJobManager();
	virtual ~EnemyJobManager();
	virtual void CharaUpdate();
};

//	ƒXƒ‰ƒCƒ€ƒNƒ‰ƒX
class Slim :public EnemyJobManager
{
protected:
	virtual void NormalAttack();
public:
	//Slim() {};
	virtual ~Slim() {};
};