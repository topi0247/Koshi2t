//
//	@file	Spawn.h
//	@brief	スポーンゲートクラス
//	@date	2016/11/25
//	@author	仁科香苗
#pragma once
#include <time.h>
#include "./../Origin.h"
//#include "./../Mesh/CD3DXMESH.h"
#include "./../Charactor/Enemy/EnemyJobManager.h"
#include "./../Read/SpawnGateRead.h"



class Spawn/* :public CD3DXMESH*/
{
private:
	int timeCount_;
	float scale_;
	D3DXVECTOR3 rot_;

	SpawnGateAttr* spawn_;
	//ParameterRead* tempParameter_;
	CharactorManager* tempCharactor_;

	//int spawnID_;		//スポーン番号
	//int amount_;		//一度に生成するエネミーの数
	//char enemyName_[30];	//生成するエネミー名
	std::vector<EnemyJobManager*> insEnemyList_;

	void SlimeSet();
	void GoblinSet();
	void SkeletonSet();
public:
	Spawn();
	~Spawn();
	std::vector<EnemyJobManager*> EnemySpawn();
	//void SpawnInit(const char* name);
	void SpawnInit(SpawnGateAttr* spawnInfo);
	//void ListSet(ParameterRead* param,CharactorManager* target);
	void ListSet(CharactorManager* target);
	void ListReset();
	D3DXVECTOR3 GetPos()const { return spawn_->pos_; };
	D3DXVECTOR3 GetRot()const { return rot_; };
	float GetScale()const { return scale_; };
	SpawnGateAttr* GetSpawnGateAttr()const { return spawn_; };

	//void SpawnRender();		//描画
};