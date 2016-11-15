//
//	@file	JobManager.h
//	@brief	職業毎の処理
//	@date	2016/11/10
//	@outher	仁科香苗

#pragma once
#include "./../Player/PlayerManager.h"
#include "./../../Read/ParameterRead.h"

//	パラメータ
struct PlayerParameter
{
	char* name_;	//職業名
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//通常攻撃力
	unsigned int specialAtk_;	//特殊攻撃力
	unsigned int def_;			//守備力
	unsigned int waitTime_;		//待機時間
	float speed_;				//移動速度
	float weight_;				//重さ
	float chargeTime_;			//チャージタイム
};

//	職業管理クラス
class JobManager :public PlayerManager
{
	//void Motion_Update();
public:
	JobManager(Controller controller);
	virtual ~JobManager();
	virtual void CharaUpdate();
};

//	剣士クラス
class SwordMan :public JobManager
{
protected:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	SwordMan(Controller controller);
};

//	魔導士クラス
class Witch :public JobManager
{
protected:	
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Witch(Controller controller);
};

//	盾士クラス
class ShieldMan :public JobManager
{
protected:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	ShieldMan(Controller controller);
};

//	爆弾士クラス
class Bomber :public JobManager
{
private:

protected:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Bomber(Controller controller);
};