//
//	@file	Main_Scene.h
//	@brief	メインゲームシーン管理クラス
//	@date	2016/11/08
//	@outher	仁科香苗
#pragma once
#include "./Origin.h"
#include "./Read/XFileRead.h"
#include "./Stage/Stage.h"
#include "./Charactor/Player/JobManager.h"
#include "./Charactor/Enemy/EnemyJobManager.h"
#include "./Collision.h"
#include "./DebugDraw/D3D11_TEXT.h"

class Main_Scene
{
	Stage* stage_;				//ステージ情報
	Collision* ray_;
	JobManager** virChar_;	//確認用仮キャラクター
	EnemyJobManager** virEnemy_;	//確認用仮キャラクター
	D3D11_TEXT* debugText_;

public:
	Main_Scene();
	~Main_Scene();

	HWND m_hWnd;

	void Init(HWND m_hWnd,ID3D11Device* m_pDevice,ID3D11DeviceContext* m_pDeviceContext);	//初期化
	HRESULT DebugInit(ID3D11DeviceContext* m_pDeviceContext);
	void Update();																			//更新
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj);										//描画
};

