#pragma once
#include <vector>
#include <d3dx9math.h>
#include "./tinyxml2.h"

using namespace tinyxml2;

//
//	@brief	スポーンゲートの属性
struct SpawnGateAttr
{
	unsigned int id_;			//スポーンゲート番号
	D3DXVECTOR3 pos_;			//座標
	D3DXVECTOR3 leftBack_;		//出現範囲座標左奥
	D3DXVECTOR3 rightFront_;	//出現範囲座標右手前
	char enemyName_[30];		//出現する敵の名前
	unsigned int amount_;		//一度に出現する数
	unsigned int interval_;		//次に出現するまでの時間(秒)
};

//
//	@brief	スポーンゲートクラス(1ステージ毎)
class SpawnGate
{
private:
	char stageName_[30];
	unsigned int count_;
	SpawnGateAttr** spawnGateList_;
	std::vector<D3DXVECTOR3> busStop_;

	void PosRead(XMLElement* element, D3DXVECTOR3 &pos);
public:
	SpawnGate(XMLElement* element);
	~SpawnGate();
	const char* GetStageName()const { return stageName_; };
	int GetCount()const { return count_; };
	std::vector<D3DXVECTOR3> GetBusStop()const { return busStop_; };
	std::vector<SpawnGateAttr*> GetStageAllSpawnGate();
};

//
//	@brief	スポーンゲート読み込みクラス
class SpawnGateRead
{
private:
	SpawnGate** spawnGateList_;		//全てのスポーンゲートのリスト
	unsigned int count_;			//すべてのスポーンゲート数
public:
	SpawnGateRead();
	~SpawnGateRead();

	void SpawnGate_Read();							//スポーンゲート情報の読み込み
	SpawnGate* GetSpawnGate(const char* stageName);	//1ステージのスポーンゲート情報の呼び出し
};