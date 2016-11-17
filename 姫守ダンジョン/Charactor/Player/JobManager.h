//
//	@file	JobManager.h
//	@brief	職業毎の処理
//	@date	2016/11/10
//	@outher	仁科香苗

#pragma once
#include "./../Player/PlayerManager.h"
#include "./../../Read/ParameterRead.h"
#include "./../../Collision.h"

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
protected:
	unsigned int timeCount_;	//攻撃時間
	unsigned int timeEnd_;		//攻撃終了時間
	//void Motion_Update();

	Collision* col_;

public:
	JobManager(Controller controller);
	virtual ~JobManager();
	virtual void CharaUpdate();
};

//	剣士クラス
class SwordMan :public JobManager
{
private:
	virtual void Normal_Attack();
	virtual void Special_Attack();
	void Normal_Attack_Collision();
public:
	SwordMan(Controller controller);
	virtual void Attack();
	//デバッグ用
	float dist;
	D3DXVECTOR3 nor;
};

//	魔導士クラス
class Witch :public JobManager
{
private:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Witch(Controller controller);
	virtual void Attack();
};

//	盾士クラス
class ShieldMan :public JobManager
{
private:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	ShieldMan(Controller controller);
	virtual void Attack();
};

//	爆弾士クラス
class Bomber :public JobManager
{
private:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Bomber(Controller controller);
	virtual void Attack();
};