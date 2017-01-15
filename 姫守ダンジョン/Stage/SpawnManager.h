//
//	@file	SpawnManager.h
//	@brief	スポーンゲート管理クラス
//	@date	2016/11/28
//	@author	仁科香苗

#pragma once
#include "./../Origin.h"
#include "./../Mesh/CD3DXMESH.h"
#include "./../Read/SpawnGateRead.h"
#include "./Spawn.h"
#include "./../Charactor/CharactorCreator.h"
#include "./../UI/TD_Graphics.h"
#include "./../Camera.h"

class SpawnManager
{
private:
	TD_Graphics* seal_UI;
	CharactorCreator* creator_;
	CD3DXMESH* spawnMesh_;
	SpawnGateRead* spawnGateRead_;
	SpawnGate* spawnGate_;

	int timeCount_;
	bool uiDrawFlg_;

	//char stageTye[30];					//現在のステージタイプ
	std::vector<Spawn*> spawnList_;			//現在存在しているスポーンゲートリスト
	std::vector<Spawn*> functionList_;		//機能しているスポーンゲートリスト
	std::vector<Spawn*> renderList_;		//描画するスポーンゲートリストリスト
	Spawn* sealSpawn_;						//封印されるスポーンゲート
	
	void SpawnSet();	//スポーンゲートの準備

public:
	SpawnManager();
	~SpawnManager();

	void Init(char* name);
	void Reset();
	void Update(/*ParameterRead* param, */CharactorManager* target);
	void SealSpawn(Spawn* spawn);
	void Render();
	std::vector<EnemyJobManager*> OutEnemy();
	std::vector<Spawn*> GetSpawnList() { return spawnList_; };

};