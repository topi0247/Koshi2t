//
//	@file	Main_Scene.h
//	@brief	メインゲームシーン管理クラス
//	@date	2016/11/08
//	@outher	仁科香苗
#pragma once
#include <vector>
#include "./Origin.h"
#include "./Read/XFileRead.h"
#include "./Stage/Stage.h"
#include "./Charactor/Player/JobManager.h"
#include "./Charactor/CharactorCreator.h"
#include "./Charactor/Enemy/EnemyJobManager.h"
#include "./Collision.h"
#include "./DebugDraw/D3D11_TEXT.h"

class Main_Scene
{
	Stage* stage_;				//ステージ情報
	Collision* ray_;
	JobManager** virChar_;	//確認用仮キャラクター
	EnemyJobManager** virEnemy_;	//確認用仮キャラクター
	/*EnemyJobManager* virEnemy_;*/

	void CollisionControl();	//衝突判定管理

	std::vector<CharactorManager*> charList_;	//ステージ上に存在するキャラクター
	std::vector<EnemyJobManager*> enemyList_;	//ステージ上に存在するエネミー


	//デバック
	D3D11_TEXT* debugText_;
public:
	Main_Scene();
	~Main_Scene();

	void Init(HWND m_hWnd,ID3D11Device* m_pDevice,ID3D11DeviceContext* m_pDeviceContext);	//初期化
	
	HRESULT DebugInit(ID3D11DeviceContext* m_pDeviceContext);								//デバッグ描画初期化
	
	void Update();																			//更新
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj);										//描画
};

