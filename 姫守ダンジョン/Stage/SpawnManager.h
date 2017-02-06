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
#include "./../Effekseer/Effect.h"

class SpawnManager
{
private:
	TD_Graphics* seal_UI;						//封印時のUI
	CharactorCreator* creator_;					//モデル読み込み用クラス
	CD3DXMESH* spawnMesh_;						//スポーンゲートのメッシュ
	SpawnGateRead* spawnGateRead_;				//スポーンゲート情報読み込みクラス
	SpawnGate* spawnGate_;						//スポーンゲート情報
	Spawn* sealSpawn_;							//封印されるスポーンゲート
	std::vector<Spawn*> spawnList_;				//現在存在しているスポーンゲートリスト
	std::vector<Spawn*> functionList_;			//機能しているスポーンゲートリスト
	std::vector<Spawn*> renderList_;			//描画するスポーンゲートリストリスト
	std::vector<CD3DXSKINMESH*> enemyMesh_List;	//描画されるエネミーメッシュリスト

	int timeCount_;		//時間カウント
	bool uiDrawFlg_;	//封印時のUI描画フラグ

	void SpawnSet();	//スポーンゲートの準備

public:
	SpawnManager();
	~SpawnManager();

	void Init(char* name);										//初期化
	void Reset();												//リセット
	void Update(CharactorManager* target);						//更新
	void SealSpawn(Spawn* spawn);								//封印
	void Render();												//描画
	CD3DXMESH* GetMesh()const { return spawnMesh_; };			//スポーンゲートのメッシュ情報取得
	std::vector<EnemyJobManager*> OutEnemy();					//生成されるエネミー
	std::vector<Spawn*> GetSpawnList() { return spawnList_; };	//スポーンゲートの情報リスト

};