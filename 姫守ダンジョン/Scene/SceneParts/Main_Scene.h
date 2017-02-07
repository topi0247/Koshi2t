//
//	@file	Main_Scene.h
//	@brief	メインゲームシーンクラス
//	@date	2016/11/08
//	@author	仁科香苗
//	@author	吉越大騎(エフェクト・UI)

#pragma once
#include <vector>
#include <time.h>
//#include "./../../Read/XFileRead.h"
//#include "./../../Read/ParameterRead.h"
//#include "./../../Read/MotionRead.h"
#include "./../../Stage/Stage.h"
#include "./../../Charactor/Player/PlayerCommon.h"
#include "./../../Charactor/CharactorCreator.h"
#include "./../../Charactor/Enemy/EnemyJobManager.h"
#include "./../../Stage/SpawnManager.h"
#include "./../../Charactor/Princess.h"
#include "./../../Collision.h"
#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"
#include "./../SceneParts/Title_Scene.h"
#include "./../SceneParts/Result_Scene.h"

#define UI_TIME 12 //時間表示に使用するUIの数
#define SEMICOLON 10
#define ENEMY_MAX 50
#define FAILED_UI_POSY 350
#define FAILED_CHOICE_POSY 850

class Main_Scene :public Scene
{
private:
	TD_Graphics* uiStart_;
	TD_Graphics* uiFailed_;
	TD_Graphics* uiRetry_[2];
	TD_Graphics* uiBack_[2];
	TD_Graphics* uiHand_;
	TD_Graphics* uiTime_[UI_TIME]; //0~9 :

	Stage* stage_;						//ステージ情報
	Princess* princess_;				//姫
	CharactorCreator* creator_;			//モデル・キャラデータ読み込みクラス
	Collision* ray_;					//当たり判定クラス
	Camera* camera_;					//カメラクラス
	SpawnManager* spawnManager_;
	std::vector<JobManager*> player_;	//プレイヤー
	std::vector<CharactorManager*> charList_;	//ステージ上に存在するキャラクター
	std::vector<CharactorManager*> killList_;	//死亡エネミーリスト

	enum scene
	{
		StartS = 0,
		MainS,
		EndS,
		NextS,
	};
	scene scene_;

	enum colored
	{
		isColor=0,
		noneColor,
	};

	bool failedFlg_;
	bool retryFlg_;
	bool nextSceneFlg_;
	bool failedChoiceFlg_;
	bool princessVoiceFlg_;
	bool startCameraMovefirstFlg_;
	bool startCameraMoveSecFlg_;
	int spawnAmount_;					//スポーンゲートの数
	int enemyCount_;
	unsigned int time_;
	float handXPos_; 
	float inputX;
	float failedUIPosY_;
	float reUIPosY_;

	void GameStart();	//ゲーム開始導入部分
	void GameMain();	//ゲームメイン
	void GameEnd();		//ゲーム終了
	void NextScene();
	void GameOverChoice();

	void CollisionControl();			//衝突判定管理
	void EnemyDestroy();	//エネミー死亡処理
	JobManager* SetCharaJob(char* name, CharaType type);

	//デバック
	D3D11_TEXT* debugText_;
	double insTime_, pushTime_;
	bool spawnFlg_;
	void PlayerDebug();
	//void EnemyDebug();
public:
	Main_Scene();
	virtual ~Main_Scene();

	void Init(/*HWND m_hWnd,ID3D11Device* m_pDevice,ID3D11DeviceContext* m_pDeviceContext*/);	//初期化
	void Destroy();
	//HRESULT DebugInit(ID3D11DeviceContext* m_pDeviceContext);								//デバッグ描画初期化
	//HRESULT EffectInit(ID3D11DeviceContext* m_pDeviceContext);
	/*void Render(D3DXMATRIX mView, D3DXMATRIX mProj);*/										//描画
	void Update();
	void Render();
	//void EffectRender();	//描画

	SceneBase* Update(SceneRoot* root);


	//デバッグ用
	DWORD start1, start2, end1, end2, result1, result2;
};