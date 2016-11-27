//
//	@file	Spawn.h
//	@brief	スポーンゲートクラス
//	@date	2016/11/24
//	@outher	仁科香苗
#pragma once
#include <time.h>
#include "./../Origin.h"
#include "./../Mesh/CD3DXMESH.h"
#include "./../Charactor/Enemy/EnemyJobManager.h"



class Spawn :public CD3DXMESH
{
private:
	int spawnID_;		//スポーン番号
	int amount_;		//一度に生成するエネミーの数
	char enemyName_[30];	//生成するエネミー名
	std::vector<EnemyJobManager*> insEnemyList_;
public:
	Spawn();
	~Spawn();
	std::vector<EnemyJobManager*> EnemySpawn();
	void SpawnInit(const char* name);
	void ListSet(ParameterRead* param,CharactorManager* target);
	void ListReset();

	void SpawnRender();		//描画
};