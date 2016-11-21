//
//	@file	PlayerManager.h
//	@brief	プレイヤー管理クラス
//	@date	2016/11/09
//	@outher	仁科香苗
#pragma once
#include "./../CharactorManager.h"
#include "./GamePad.h"

enum Controller
{
	player1 = 0,
	player2,
	player3,
	player4,
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
	Controller controller_;	//コントローラー番号

	bool callFlg_;			//姫呼びフラグ
	int attackCount_;		//攻撃ボタンカウント

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
	void Revival();									//復活
	//D3DXVECTOR3 Princess_Call();					//姫呼び
	bool GetAliveFlg()const;						//生存フラグ取得

	//デバッグ用
	int GetAtkCnt() { return attackCount_; };
	AttackState GetAtkState() { return atkNo_; };
	float GetYaw() { return m_Yaw; };
};