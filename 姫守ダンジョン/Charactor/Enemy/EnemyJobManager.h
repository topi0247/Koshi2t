//
//	@file	JobManager.h
//	@brief	敵ごとの処理
//	@date	2016/11/13
//	@outher	吉越大騎

#pragma once
#include "./../Enemy/EnemyManager.h"

//	パラメータ
struct EnemyParameter
{
	unsigned char name_[30];	//敵の名
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//通常攻撃力
	unsigned int def_;			//守備力
	unsigned int waitTime_;		//待機時間
	float speed_;				//移動速度
	float weight_;				//重さ
};

//	職業管理クラス
class EnemyJobManager :public EnemyManager
{
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