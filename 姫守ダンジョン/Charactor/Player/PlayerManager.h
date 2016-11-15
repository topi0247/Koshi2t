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

	bool aliveFlg_;			//生存フラグ

	virtual void Normal_Attack() = 0;	//通常攻撃
	virtual void Special_Attack() = 0;	//特殊攻撃
	virtual void Attack();				//攻撃
	virtual void Move(float speed);		//移動処理
	virtual void Dead();				//死亡
	virtual void Motion_Update();		//モーション更新

public:
	PlayerManager() {};
	virtual ~PlayerManager() {};

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);

	D3DXVECTOR3 Princess_Call() { return m_vPos; };	//姫呼び
	bool GetAliveFlg()const { return aliveFlg_; };	//生存フラグ取得
	void Revival();									//復活

};