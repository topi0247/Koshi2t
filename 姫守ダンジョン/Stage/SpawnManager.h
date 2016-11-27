#pragma once
#include "./../Origin.h"
#include "./Spawn.h"

template<class temp>
class SpawnManager
{
private:
	char stageTye[30];					//現在のステージタイプ
	std::vector<Spawn> spawnList_;		//現在存在しているスポーンゲートリスト
	std::vector<Spawn> functionList_;	//機能しているスポーンゲートリスト
	std::vector<Spawn> renderList_;		//描画するスポーンゲートリストリスト
	std::vector<Spawn> killList_;		//消滅するスポーンゲートリスト

	void SpawnSet();	//スポーンゲートの準備
public:
	std::vector<temp> OutEnemy();
	void Init();
	void Update();
	void Render();
};