#pragma once
#include <list>
#include "./CharactorManager.h"
#include "./Player/PlayerManager.h"


class Princess :public CharactorManager
{
private:
	std::list<PlayerManager*> deadCharaList_;	//死んだプレイヤーリスト
	D3DXVECTOR3 destination_;		//移動目的地
	float moveSpeed_;				//移動速度
	unsigned int sealTime_;			//封印にかかる時間
	unsigned int revivalTime_;		//蘇生にかかる時間

	virtual void Move(float speed);	//移動
	virtual void Motion_Update();	//モーション更新
	virtual void Dead() {};
	virtual void Attack() {};
	void Seal();			//封印
	void Resuscitation();			//蘇生
public:
	Princess();
	virtual ~Princess();

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);		//初期化・読み込み
	virtual void CharaUpdate();						//更新
	virtual void DamageCalc(unsigned int atk);		//ダメージ計算
	void SetDestination(D3DXVECTOR3 pos);			//目的地セット
	void SetDeadCharaList(PlayerManager* chara);
};

