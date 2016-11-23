//
//	@file	JobManager.h
//	@brief	敵ごとの処理
//	@date	2016/11/13
//	@outher	吉越大騎

#pragma once
#include "./../Enemy/EnemyManager.h"


//	職業管理クラス
class EnemyJobManager :public EnemyManager
{
protected:
public:
	EnemyJobManager();
	virtual ~EnemyJobManager();
	virtual void CharaUpdate();
};

//	スライムクラス
class Slim :public EnemyJobManager
{
protected:
	virtual void NormalAttack();
public:
	//Slim() {};
	virtual ~Slim() {};
};