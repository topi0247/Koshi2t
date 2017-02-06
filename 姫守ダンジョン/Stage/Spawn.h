//
//	@file	Spawn.h
//	@brief	スポーンゲートクラス
//	@date	2016/11/25
//	@author	仁科香苗
#pragma once
#include <time.h>
#include "./../Origin.h"
#include "./../Charactor/Enemy/EnemyJobManager.h"
#include "./../Read/SpawnGateRead.h"



class Spawn
{
private:
	int timeCount_;		//時間カウント
	float scale_;		//サイズ
	D3DXVECTOR3 rot_;	//回転

	SpawnGateAttr* spawn_;							//スポーン情報
	CharactorCreator* creator_;						//モデル読み込み
	CharactorManager* tempCharactor_;				//生成されるエネミー情報一時保存用
	CD3DXSKINMESH* enemyMesh_;						//生成されるエネミーメッシュ
	std::vector<EnemyJobManager*> insEnemyList_;	//一度に生成されたエネミーリスト

public:
	Spawn();
	~Spawn();
	void SpawnInit(SpawnGateAttr* spawnInfo, CD3DXSKINMESH* mesh);	//初期化
	void ListSet(CharactorManager* target);							//スポーンリストセット
	void ListReset();												//スポーンリセット
	std::vector<EnemyJobManager*> EnemySpawn();						//エネミーの生成
	D3DXVECTOR3 GetPos()const { return spawn_->pos_; };				//スポーンゲートの座標取得
	D3DXVECTOR3 GetRot()const { return rot_; };						//スポーンゲートの回転取得
	float GetScale()const { return scale_; };						//スポーンゲートのスケール取得
	SpawnGateAttr* GetSpawnGateAttr()const { return spawn_; };		//スポーンゲートの情報取得
};