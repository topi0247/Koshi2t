//
//	@file	Main_Scene.cpp
//	@brief	ゲームメインシーン
//	@date	2016/11/08
//	@author	仁科香苗
//	@author 吉越大騎(エフェクト・UI)

//#include "./Main_Scene.h"
#include "./../SceneParts/Main_Scene.h"

//
//	@brief	コンストラクタ
Main_Scene::Main_Scene()
{
	camera_ = new Camera;
	debugText_ = new D3D11_TEXT;
	creator_ = new CharactorCreator;
	uiStart_ = new TD_Graphics;
	for (int i = 0; i < 2; i++)
	{
		uiRetry_[i] = new TD_Graphics;
		uiBack_[i] = new TD_Graphics;
	}
	uiHand_ = new TD_Graphics;
	uiFailed_ = new TD_Graphics;
	for (int i = 0; i < UI_TIME; i++)
	{
		uiTime_[i] = new TD_Graphics;
	}
}

//
//	@brief	デストラクタ
Main_Scene::~Main_Scene()
{
	delete camera_;
	camera_ = nullptr;
	delete creator_;
	creator_ = nullptr;
	delete uiStart_;
	uiStart_ = nullptr;
	delete uiFailed_;
	uiFailed_ = nullptr;
	for (int i = 0; i < 2; i++)
	{
		delete uiRetry_[i];
		uiRetry_[i] = nullptr;
		delete uiBack_[i];
		uiBack_[i] = nullptr;
	}
	delete uiHand_;
	uiHand_ = nullptr;
	for (int i = 0; i < UI_TIME; i++)
	{
		delete uiTime_[i];
		uiTime_[i] = nullptr;
	}
}

//
//	@brief	初期化
void Main_Scene::Init()
{
	camera_->movePow_ = D3DXVECTOR3(-3, 1, -15);

	stage_ = new Stage;
	spawnManager_ = new SpawnManager;
	stage_->Init("ステージ5");
	spawnManager_->Init("スポーン");


	JobManager* ply;
	for (int i = 0; i < 4; i++)
	{
		player_.push_back(ply);
	}
	player_[Player1] = SetCharaJob(CharactorCreator::player1_, Player1);
	player_[Player1]->CharaInit(CharactorCreator::player1_);
	player_[Player1]->m_Pos = D3DXVECTOR3(-3, 0, -10);
	player_[Player2] = SetCharaJob(CharactorCreator::player2_, Player2);
	player_[Player2]->CharaInit(CharactorCreator::player2_);
	player_[Player2]->m_Pos = D3DXVECTOR3(-1.5, 0, -10);
	player_[Player3] = SetCharaJob(CharactorCreator::player3_, Player3);
	player_[Player3]->CharaInit(CharactorCreator::player3_);
	player_[Player3]->m_Pos = D3DXVECTOR3(1.5, 0, -10);
	player_[Player4] = SetCharaJob(CharactorCreator::player4_, Player4);
	player_[Player4]->CharaInit(CharactorCreator::player4_);
	player_[Player4]->m_Pos = D3DXVECTOR3(3, 0, -10);

	princess_ = new Princess;
	princess_->CharaInit("姫");
	princess_->m_Pos = D3DXVECTOR3(0, 0, -12);
	princess_->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
	princess_->SetSpawn(spawnManager_->GetSpawnList());

	for (int i = 0; i < 4; i++)
	{
		charList_.push_back(player_[i]);
	}
	charList_.push_back(princess_);

	//UI
	D3DXVECTOR2 scale(1623, 336);
	uiStart_->Init(L"./UI/UI_Tex/start_font.png", scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	scale = D3DXVECTOR2(128, 256);
	float rect = 0.09;
	for (int i = 0; i < UI_TIME; i++)
	{
		uiTime_[i]->Init(L"./UI/UI_Tex/number.png", scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f + i*rect, rect + i*rect));
	}

	D3DXVECTOR2 ui_scale(1217.25, 450);
	uiFailed_->Init(L"./UI/UI_Tex/failure_font.png", ui_scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));

	scale = D3DXVECTOR2(640, 116.5);
	uiRetry_[isColor]->Init(L"./UI/UI_Tex/retry2.png", scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	uiRetry_[noneColor]->Init(L"./UI/UI_Tex/retry1.png", scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	scale = D3DXVECTOR2(360, 120);
	uiBack_[isColor]->Init(L"./UI/UI_Tex/back2.png", scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	uiBack_[noneColor]->Init(L"./UI/UI_Tex/back1.png", scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	scale = D3DXVECTOR2(150, 150);
	uiHand_->Init(L"./UI/UI_Tex/choice_hand.png", scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	retryFlg_ = true;
	nextSceneFlg_ = false;
	failedFlg_ = false;
	failedChoiceFlg_ = false;
	princessVoiceFlg_ = true;
	startCameraMovefirstFlg_ = true;
	startCameraMoveSecFlg_ = false;
	time_ = 0;
	scene_ = StartS;
	enemyCount_ = 0;
	handXPos_ = 600;
	failedUIPosY_ = -600;
	reUIPosY_ = 1080;
	Sound::getInstance().BGM_play("SENTOU");
}

//
//	@brief	職業セット
JobManager* Main_Scene::SetCharaJob(char* name, CharaType type)
{
	JobManager* temp;
	if (strcmp(name, "剣士") == 0)
	{
		temp = new SwordMan(type);
	}
	else if (strcmp(name, "盾士") == 0)
	{
		temp = new ShieldMan(type);
	}
	else if (strcmp(name, "爆弾士") == 0)
	{
		temp = new Bomber(type);
	}
	else if (strcmp(name, "魔導士") == 0)
	{
		temp = new Witch(type);
	}

	return temp;
}

//
//	@brief	解放
void Main_Scene::Destroy()
{
	Sound::getInstance().BGM_stop("SENTOU");
	charList_.clear();
	charList_.shrink_to_fit();
	player_.clear();

	delete stage_;
	stage_ = nullptr;
	delete spawnManager_;
	spawnManager_ = nullptr;
}


//
//	@brief	シーン遷移更新
SceneBase* Main_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;

	Update();

	if (scene_ == NextS)
	{
		if (!failedFlg_)
		{
			Result_Scene::clearFlg_ = true;
			next = new Result_Scene;
		}
		else
		{
			GameOverChoice();
			if (nextSceneFlg_)
			{
				if (retryFlg_)
				{
					next = new Main_Scene;
				}
				else
				{
					next = new CharactorSelection_Scene;
				}
			}
		}
	}


	return next;
}

//
//	@brief	更新
void Main_Scene::Update()
{
	switch (scene_)
	{
	case MainS:
		GameMain();
		break;
	case EndS:
		GameEnd();
		break;
	case StartS:
		GameStart();
		break;
	case NextS:
		NextScene();
		break;
	default:
		break;
	}
	//#ifdef _DEBUG
		//リセット処理(デバッグ用)
	if (GetKeyState('R') & 0x80)
	{
		for (auto c : charList_)
		{
			c->Reset();
		}
		charList_.clear();

		for (int i = 0; i < 4; i++)
		{
			charList_.push_back(player_[i]);
		}
		charList_.push_back(princess_);
		spawnManager_->Reset();
		enemyCount_ = 0;
		princess_->SetSpawn(spawnManager_->GetSpawnList());
	}
	if (GetKeyState('C') & 0x80)
	{
		scene_ = EndS;
	}
	if (GetKeyState('F') & 0x80)
	{
		failedFlg_ = true;
		scene_ = EndS;
	}
	//#endif
}


//
//	@brief	ゲーム開始
void Main_Scene::GameStart()
{
	if (startCameraMovefirstFlg_)
	{
		startCameraMoveSecFlg_ = camera_->Main_Start_FirstUpdate();
	}
	bool next = false;
	if (startCameraMoveSecFlg_)
	{
		startCameraMovefirstFlg_ = false;
		next = camera_->Main_Start_SecondUpdate();
	}

	if (next)
	{
		scene_ = MainS;
	}
}

//
//	@brief	ゲームメイン
void Main_Scene::GameMain()
{
	//時間カウント
	++time_;

	//カメラ移動
	camera_->gazePoint_ = princess_->m_Pos;
	//camera_->gazePoint_ = player_[Player1]->m_Pos;
	camera_->Main_Game_Update();

	if (enemyCount_ < ENEMY_MAX)
	{
		spawnManager_->Update(princess_);
		std::vector<EnemyJobManager*> temp = spawnManager_->OutEnemy();
		if (!temp.empty())
		{
			for (auto e : temp)
			{
				++enemyCount_;
				charList_.push_back(e);
			}
			temp.clear();
		}
	}

	//存在しているすべてのキャラクターセット
	CharactorManager::allCharaList_ = charList_;

	//エネミー、プレイヤーと姫情報の更新
	EnemyManager::princess_ = princess_;
	EnemyManager::playerList_ = player_;

	//キャラ更新
	for (auto chara : charList_)
	{
		start1 = timeGetTime();
		chara->CharaUpdate();
		end1 = timeGetTime();
		result1 = end1 - start1;

		if (chara->GetCharaType() == Enemy && !chara->GetAliveFlg())
		{
			killList_.push_back(chara);
		}
	}

	//姫の目的地更新
	D3DXVECTOR3 pos = princess_->m_Pos;
	CharaType no = PrincessT;
	double timing = 0;
	for (int i = 0; i < 4; i++)
	{
		if (timing < player_[i]->GetCallTiming())
		{
			timing = player_[i]->GetCallTiming();
			no = player_[i]->GetCharaType();
		}
	}
	if (no != PrincessT)
	{
		pos = player_[no]->GetCallPos();
	}
	princess_->SetDestination(pos);

	//スポーンゲート消滅
	spawnManager_->SealSpawn(princess_->SealSpawn());

	//衝突判定の更新
	CollisionControl();

	//キャラの移動更新
	for (auto chara : charList_)
	{
		chara->Move_Update();
	}

	//エネミー死亡処理更新
	EnemyDestroy();

	//死亡プレイヤー更新
	int deadCount = 0;
	for (int i = 0; i < 4; i++)
	{
		if (!player_[i]->GetAliveFlg() && !player_[i]->GetRevivalFlg())
		{
			princess_->SetDeadCharaList(player_[i]);
			++deadCount;
		}
	}

	//ゲーム終了
	//姫死亡 又は プレイヤー全滅
	if (!princess_->GetAliveFlg() || deadCount == 4)
	{
		failedFlg_ = true;
		scene_ = EndS;
	}
	//スポーンゲートすべて破壊
	if (spawnManager_->GetSpawnList().empty())
	{
		scene_ = EndS;
		Sound::getInstance().SE_play("P_STEGECLEAR");
	}
}

//
//	@brief	ゲーム終了
void Main_Scene::GameEnd()
{
	//モーションセット
	if (failedFlg_)
	{
		princess_->DeadMotion();
		Sound::getInstance().BGM_stop("SENTOU");
	}
	for (auto p : player_)
	{
		p->SetEndMotion(failedFlg_);
		GamePad::stopVibration(p->GetCharaType());
	}

	static int endCount = 0;
	if (++endCount % (FPS * 5) == 0)
	{
		scene_ = NextS;
		endCount = 0;
	}

#ifdef _DEBUG
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		scene_ = StartS;

		princess_->SetSpawn(spawnManager_->GetSpawnList());

		for (auto c : charList_)
		{
			c->Reset();
		}
		//enemyList_.clear();
		charList_.clear();

		for (int i = 0; i < 4; i++)
		{
			charList_.push_back(player_[i]);
		}
		charList_.push_back(princess_);
		spawnManager_->Reset();

		princess_->SetSpawn(spawnManager_->GetSpawnList());
}
#endif //_DEBUG
}

//
//	@brief	次シーンまでの準備
void Main_Scene::NextScene()
{
	D3DXVECTOR3 vec(0, 0, 0);
	if (failedUIPosY_ < FAILED_UI_POSY)
	{
		failedUIPosY_ += 10;
	}
	if (reUIPosY_ > FAILED_CHOICE_POSY)
	{
		reUIPosY_ -= 10;
	}
	else
	{
		failedChoiceFlg_ = true;
	}
	vec = D3DXVECTOR3(sinf(princess_->m_Yaw)*-1, 3, cosf(princess_->m_Yaw)*-1);
	camera_->movePow_ = princess_->m_Pos + vec;
}

//
//	@brief	ゲームオーバー
void Main_Scene::GameOverChoice()
{
	if (princessVoiceFlg_)
	{
		Sound::getInstance().SE_play("P_FAILED");
		Sound::getInstance().SE_play("FAILED");
		princessVoiceFlg_ = false;
	}

	float inputX=0;
	//for (int i = 0; i < 4; i++)
	//{
		inputX = GamePad::getAnalogValue(Player1, GamePad::AnalogName::AnalogName_LeftStick_X);
		if (failedChoiceFlg_&&GamePad::checkInput(Player1, GamePad::A))
		{
			nextSceneFlg_ = true;
		}
	//}

	if (inputX > 0.3)
	{
		handXPos_ = 1330;
		retryFlg_ = false;
	}
	else if (inputX < -0.3)
	{
		handXPos_ = 620;
		retryFlg_ = true;
	}
	
	GamePad::update();

}

//
//	@brief	エネミー死亡処理
void Main_Scene::EnemyDestroy()
{
	if (!killList_.empty())
	{
		for (auto c : killList_)
		{
			//キャラリストから探す
			auto cl = std::find(std::begin(charList_), std::end(charList_), c);

			//　オブジェクトの終了処理
			delete (*cl);
			//	リストから外す
			charList_.erase(cl);
			--enemyCount_;
		}
		killList_.clear();
	}
}

//
//	@brief	衝突判定管理
void Main_Scene::CollisionControl()
{

	//当たり判定
	float fDistance = 0;
	D3DXVECTOR3 vNormal;

	//壁との衝突判定
	for (auto chara : charList_)
	{
		start2 = timeGetTime();
		if (chara->m_Dir != D3DXVECTOR3(0, 0, 0))
		{
			if (ray_->RayIntersect(chara->m_Pos, chara->m_Dir, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.3)
			{
				if (chara->GetKnockBackFlg() == true)
				{
					chara->SetKnockBackFlg(false);
				}
				//chara->StopMove();
				//当たり状態なので、滑らせる
				chara->SlipMove(ray_->Slip(chara->m_Dir, vNormal));
				//滑りベクトル先の壁とのレイ判定 ２重に判定	
				if (ray_->RayIntersect(chara->m_Pos, chara->m_Dir, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.2)
				{
					chara->StopMove();
				}
			}
		}
		end2 = timeGetTime();
		result2 = end2 - start2;
	}

	//周辺にキャラクターがいるかどうか
	for (int i = 0; i < charList_.size(); i++)
	{
		for (int j = i + 1; j < charList_.size(); j++)
		{
			if (ray_->CheckSpaceNo(charList_[i]->GetSpaceNo(), charList_[j]->GetSpaceNo(), 1, 2))
			{
				charList_[i]->SetAroundChara(charList_[j]);
				charList_[j]->SetAroundChara(charList_[i]);
			}
		}
	}
}

//
//	@brief			描画
void Main_Scene::Render()
{

	//ステージの描画
	stage_->Render();

	//キャラ描画
	for (auto chara : charList_)
	{
		chara->CharaRender();
	}

	//スポーンゲートの描画
	spawnManager_->Render();

	//エフェクトの更新と描画
	Effect::getInstance().SetCamera(camera_->movePow_, camera_->gazePoint_);
	Effect::getInstance().Update();
	Effect::getInstance().Draw();

	//UI描画
	if (scene_ != NextS)
	{
		for (auto p : player_)
		{
			p->UIRender();
		}
	}
	//時間描画
	float posX = 1400;
	float space = 80;
	D3DXVECTOR2 scale(0.5, 0.5);
	//分
	int minutes10 = time_ / (FPS*FPS * 10) % 6;// time_ / FPS % 6;
	int minutes1 = time_ / (FPS*FPS) % 10;// time_ / FPS;
	uiTime_[minutes10]->Render(D3DXVECTOR2(posX, 0), scale, true);
	uiTime_[minutes1]->Render(D3DXVECTOR2(posX + space * 0.8, 0), scale, true);
	uiTime_[SEMICOLON]->Render(D3DXVECTOR2(posX + space * 1.33, 0), scale, true);
	//秒
	int second10 = time_ / (FPS * 10) % 6;
	int second1 = time_ / FPS % 10;
	uiTime_[second10]->Render(D3DXVECTOR2(posX + space * 2, 0), scale, true);
	uiTime_[second1]->Render(D3DXVECTOR2(posX + space * 2.8, 0), scale, true);
	uiTime_[SEMICOLON]->Render(D3DXVECTOR2(posX + space * 3.3, 0), scale, true);
	//ミリ秒
	int conma10 = time_ / 10 % 6;
	int conma1 = time_ % 10;
	uiTime_[conma10]->Render(D3DXVECTOR2(posX + space * 4, 0), scale, true);
	uiTime_[conma1]->Render(D3DXVECTOR2(posX + space * 4.8, 0), scale, true);

	float posY = 380;
	posX = 180;
	if (scene_ == StartS && startCameraMoveSecFlg_)
	{
		//static float posX = 180;
		uiStart_->Render(D3DXVECTOR2(posX, posY), D3DXVECTOR2(1, 1), true);
	}
	else if (scene_ == EndS && !failedFlg_)
	{
		Result_Scene::m10_Time = minutes10;
		Result_Scene::m1_Time = minutes1;
		Result_Scene::s10_Time = second10;
		Result_Scene::s1_Time = second1;
		Result_Scene::c10_Time = conma10;
		Result_Scene::c1_Time = conma1;

		//uiFailed_->Render(D3DXVECTOR2(posX, posY), D3DXVECTOR2(1, 1), true);
	}
	else if (scene_ == NextS && failedFlg_)
	{
		uiFailed_->Render(D3DXVECTOR2(350, failedUIPosY_), D3DXVECTOR2(1, 1), true);
		uiHand_->Render(D3DXVECTOR2(handXPos_, reUIPosY_ + 100), D3DXVECTOR2(1, 1), true);
		if (retryFlg_)
		{
			uiRetry_[isColor]->Render(D3DXVECTOR2(300, reUIPosY_), D3DXVECTOR2(1, 1), true);
			uiBack_[noneColor]->Render(D3DXVECTOR2(1150, reUIPosY_), D3DXVECTOR2(1, 1), true);
		}
		else
		{
			uiRetry_[noneColor]->Render(D3DXVECTOR2(300, reUIPosY_), D3DXVECTOR2(1, 1), true);
			uiBack_[isColor]->Render(D3DXVECTOR2(1150, reUIPosY_), D3DXVECTOR2(1, 1), true);
		}
	}

	//#ifdef _DEBUG
		//PlayerDebug();
		//EnemyDebug();
	//#endif // _DEBUG

	camera_->Render();
}

void Main_Scene::PlayerDebug()
{
	//デバッグ描画
	char str[256];
	sprintf(str, "handpos:%f", handXPos_);
	debugText_->Render(str, 0, 50);

	sprintf(str, "stickX:%f", GamePad::getAnalogValue(Player1, GamePad::AnalogName::AnalogName_LeftStick_X));
	debugText_->Render(str, 0, 80);

}

//void Main_Scene::EnemyDebug()
//{
//	char str[256];
//	if (!enemyList_.empty())
//	{
//		sprintf(str, "count:%d", enemyList_.size());
//		debugText_->Render(str, 0, 30);
//		
//	}
//}