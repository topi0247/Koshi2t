//
//	@file	Princess.h
//	@brief	姫クラス
//	@date	2016/12/01
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#pragma once
#include <list>
#include "./CharactorManager.h"
#include "./Player/PlayerManager.h"
#include "./../Stage/Spawn.h"


class Princess :public CharactorManager
{
private:
	std::vector<Spawn*> spawnPosList_;
	Spawn* sealSpawn_;
	std::vector<PlayerManager*> deadCharaList_;	//死んだプレイヤーリスト
	D3DXVECTOR3 destination_;					//移動目的地
	int destinationSpaceNo_;					//移動目的地空間番号
	float moveSpeed_;							//移動速度
	unsigned int sealTime_;						//封印にかかる時間
	unsigned int revivalTime_;					//蘇生にかかる時間
	bool sealFlg_;
	bool resFlg_;

	virtual void Move(float speed);				//移動
	//virtual void Motion_Update();				//モーション更新
	virtual void Dead() {};
	virtual void Attack() {};
	void Seal();					//封印
	void Resuscitation();			//蘇生
	virtual void SetParameter(char* name);
public:
	Princess();
	virtual ~Princess();

	Spawn* SealSpawn();
	virtual void Reset();
	virtual void CharaUpdate();						//更新
	virtual void DamageCalc(unsigned int atk);		//ダメージ計算
	void SetDestination(D3DXVECTOR3 pos);			//目的地セット
	void SetDeadCharaList(PlayerManager* chara);
	void SetSpawn(std::vector<Spawn*> spawn);
	void DeadMotion();
};

