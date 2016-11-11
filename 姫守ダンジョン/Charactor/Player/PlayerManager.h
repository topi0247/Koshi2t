//
//	@file	PlayerManager.h
//	@brief	プレイヤー管理クラス
//	@date	2016/11/09
//	@outher	仁科香苗
#pragma once
#include "./../CharactorManager.h"
#include "./GamePad.h"
#include "./../../DebugDraw/D3D11_TEXT.h"

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

	Controller controller_;	//Controller番号

	virtual void NormalAttack() = 0;	//通常攻撃
	virtual void SpecialAttack() = 0;	//特殊攻撃
	virtual void Attack();				//攻撃
	virtual void Move(float speed);		//移動処理
	virtual void Dead();				//死亡
	virtual void Motion_Update() {};	//モーション更新
	void Revival();						//復活
public:
	PlayerManager() {};
	virtual ~PlayerManager() {};

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);
};