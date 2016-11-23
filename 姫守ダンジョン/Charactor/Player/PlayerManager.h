//
//	@file	PlayerManager.h
//	@brief	プレイヤー管理クラス
//	@date	2016/11/09
//	@outher	仁科香苗
#pragma once
#include "./../CharactorManager.h"
#include "./GamePad.h"

//	パラメータ
struct PlayerParameter
{
	char name_[30];				//職業名
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//通常攻撃力
	unsigned int specialAtk_;	//特殊攻撃力
	unsigned int def_;			//守備力
	unsigned int chargeTime_;	//チャージタイム
	float specialAttackTime_;	//待機時間
	float moveSpeed_;			//移動速度
	float specialMoveSpeed_;	//特殊移動速度
	float weight_;				//重さ
	float attackReach_;			//攻撃リーチ
	float attackRange_;			//攻撃範囲
	float scale_;				//スケール
};

class PlayerManager : public CharactorManager
{
protected:

	//モーション番号
	enum MotionNo
	{
		waitM = 0,
		walkM,
		normalAtkM,
		specialAtkM,
		deadM,
		revivalM,
	};

	//攻撃状態番号
	enum AttackState
	{
		noAtk = 0,	//攻撃していない
		waitAtk,	//攻撃待機
		normalAtk,	//通常攻撃
		charge,		//チャージ
		specialAtk,	//特殊攻撃
	};

	MotionNo motionNo_;		//モーション番号
	AttackState atkNo_;		//攻撃状態番号
	PlayerParameter* param_;

	bool callFlg_;			//姫呼びフラグ

	virtual void Normal_Attack() = 0;	//通常攻撃
	virtual void Special_Attack() = 0;	//特殊攻撃
	//virtual void Attack();			//攻撃
	virtual void Move(float speed);		//移動処理
	virtual void Dead();				//死亡
	virtual void Motion_Update();		//モーション更新


public:
	PlayerManager() {};
	virtual ~PlayerManager() {};

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);	//初期化と読み込み
	virtual void DamageCalc(unsigned int atk);					//ダメージ計算
	void Revival();									//復活
	void Princess_Call();					//姫呼び
	bool GetAliveFlg()const;						//生存フラグ取得

	//デバッグ用
	//int GetAtkCnt() { return attackCount_; };
	AttackState GetAtkState() { return atkNo_; };
	float GetYaw() { return m_Yaw; };
};