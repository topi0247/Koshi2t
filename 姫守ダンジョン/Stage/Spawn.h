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


using namespace STATICMESH;

class Spawn :public CD3DXMESH
{
private:
	HWND hWnd_;
	ID3D11Device* pDevice_;
	ID3D11DeviceContext* pDeviceContext_;

	int spawnID_;		//スポーン番号
	int amount_;		//一度に生成するエネミーの数
	char enemyName_[30];	//生成するエネミー名
	std::vector<EnemyJobManager*> insEnemyList_;
public:
	Spawn();
	~Spawn();
	std::vector<EnemyJobManager*> EnemySpawn();
	void SpawnInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* name);
	void ListSet(ParameterRead* param,CharactorManager* target);
	void ListReset();

	void SpawnRender(D3DXMATRIX mView, D3DXMATRIX mProj);		//描画
};