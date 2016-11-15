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

class PlayerManager : public CharactorManager
{
protected:

	enum MotionNo
	{
		waitM=0,
		walkM,
		normalAtkM,
		spcialAtkM,
		deadM,
		revivalM,
	};

	MotionNo motionNo_;		//モーション番号
	Controller controller_;	//コントローラー番号
	PlayerParameter playerParam_;	//プレイヤーパラメータ

	bool aliveFlg_;			//生存フラグ
	int attackCount_;		//攻撃ボタンカウント

	virtual void Normal_Attack() = 0;	//通常攻撃
	virtual void Special_Attack() = 0;	//特殊攻撃
	virtual void Attack();				//攻撃
	virtual void Move(float speed);		//移動処理
	virtual void Dead();				//死亡
	virtual void Motion_Update();		//モーション更新


public:
	PlayerManager() {};
	virtual ~PlayerManager() {};

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);	//初期化と読み込み
	void Revival();									//復活
	D3DXVECTOR3 Princess_Call();	//姫呼び
	bool GetAliveFlg()const;	//生存フラグ取得

	//デバッグ用
	int GetAtkCnt() { return attackCount_; };
	int atk;
	float GetYaw() { return m_fYaw; };
};