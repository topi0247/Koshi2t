//
//	@file	EnemyManager.h
//	@brief	敵管理クラス
//	@date	2016/11/13
//	@outher	吉越大騎

#pragma once
#include "./../CharactorManager.h"
#include "./../../DebugDraw/D3D11_TEXT.h"

class EnemyManager : public CharactorManager
{
private:
	D3DXVECTOR3 targetPos_;
	enum TargetObject
	{
		princess = 0,
		player,
	};
	TargetObject targetObj;
protected:

	virtual void NormalAttack() = 0;	//通常攻撃
	virtual void Attack();				//攻撃
	virtual void Move(float speed);		//移動処理
	virtual void Dead();				//死亡
	virtual void Motion_Update() {};	//モーション更新
	void Spawn();						//敵スポーン

public:
	EnemyManager() {};
	virtual ~EnemyManager() {};
	
	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);		//初期化・読み込み

	void CheckNearPlayer(D3DXVECTOR3 position);	//近くにいるか判別
};

