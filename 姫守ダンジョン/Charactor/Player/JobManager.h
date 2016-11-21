//
//	@file	JobManager.h
//	@brief	職業毎の処理
//	@date	2016/11/10
//	@outher	仁科香苗

#pragma once
#include "./../Player/PlayerManager.h"
#include "./../../Read/ParameterRead.h"
#include "./../../Collision.h"
#include "./../../Mesh/CD3DXMESH.h"
#include "./Job/WeaponBall.h"
#include "./../../Read/ParameterRead.h"


//	パラメータ
struct PlayerParameter
{
	char* name_;				//職業名
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//通常攻撃力
	unsigned int specialAtk_;	//特殊攻撃力
	unsigned int def_;			//守備力
	float specialAttackTime_;	//待機時間
	float chargeTime_;			//チャージタイム
	float moveSpeed_;			//移動速度
	float specialMoveSpeed_;	//特殊移動速度
	float weight_;				//重さ
	float attackReach_;			//攻撃リーチ
	float attackRange_;			//攻撃範囲
	float scale_;				//スケール
};

//	職業管理クラス
class JobManager :public PlayerManager
{
protected:
	unsigned int timeCount_;	//攻撃時間
	unsigned int timeEnd_;		//攻撃終了時間
	PlayerParameter* param_;

	//void Motion_Update();

	Collision* col_;

public:
	JobManager(CharaType charaType);
	virtual ~JobManager();
	virtual void CharaUpdate();
	//template<class> p;
	void SetParameter(JobParameter* param);
	//PlayerParameter GetParam()const;
	bool hit;//デバッグ用
};

