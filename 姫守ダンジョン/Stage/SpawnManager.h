#pragma once
#include "./../Origin.h"
#include "./../Mesh/CD3DXMESH.h"
#include "./../Read/SpawnGateRead.h"
#include "./Spawn.h"

class SpawnManager
{
private:
	CD3DXMESH* spawnMesh_;
	SpawnGateRead* spawnGateRead_;
	SpawnGate* spawnGate_;

	int timeCount_;

	//char stageTye[30];					//現在のステージタイプ
	std::vector<Spawn*> spawnList_;			//現在存在しているスポーンゲートリスト
	std::vector<Spawn*> functionList_;		//機能しているスポーンゲートリスト
	std::vector<Spawn*> renderList_;		//描画するスポーンゲートリストリスト
	Spawn* sealSpawn_;						//封印されるスポーンゲート
	
	void SpawnSet();	//スポーンゲートの準備

public:
	SpawnManager();
	~SpawnManager();

	void Init(const char* name);
	void Reset();
	void Update(ParameterRead* param, CharactorManager* target);
	void SealSpawn(Spawn* spawn);
	void Render();
	std::vector<EnemyJobManager*> OutEnemy();
	std::vector<Spawn*> GetSpawnList() { return spawnList_; };

};