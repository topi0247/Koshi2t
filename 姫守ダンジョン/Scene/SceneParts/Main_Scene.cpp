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
	stage_ = new Stage;
	JobManager* ply;
	for (int i = 0; i < 4; i++)
	{
		virChar_.push_back(ply);
	}

	virChar_[Player1] = new SwordMan(Player1);
	virChar_[Player2] = new ShieldMan(Player2);
	virChar_[Player3] = new Witch(Player3);
	virChar_[Player4] = new Bomber(Player4);
	princess_ = new Princess;

	for (int i = 0; i < 4; i++)
	{
		charList_.push_back(virChar_[i]);
	}
	charList_.push_back(princess_);
	scene_ = StartS;

	//slime_ = new CD3DXSKINMESH;
	//virEnemy_ = new Slim;

	spawnManager_ = new SpawnManager;

	camera_ = new Camera;

	//Title_UI["TITLE_UI"] = new TD_Graphics;
	debugText_ = new D3D11_TEXT;
}

//
//	@brief	デストラクタ
Main_Scene::~Main_Scene()
{
	//delete stage_;
	//stage_ = nullptr;

	//delete spawnManager_;
	//spawnManager_ = nullptr;


	for (int i = 0; i < 4; i++)
	{
		SAFE_DELETE(virChar_[i]);
	}
	SAFE_DELETE(princess_);
	//SAFE_DELETE(virEnemy_);
	//SAFE_DELETE(slime_);
	//delete debugText_;
	//debugText_ = nullptr;

	//delete xfile;
	//xfile = nullptr;
	//delete parameter;
	//parameter = nullptr;

	delete camera_;
	camera_ = nullptr;

	/*delete uisword_;
	uisword_ = nullptr;
	delete uiseeld_;
	uiseeld_ = nullptr;
	delete uimagic_;
	uimagic_ = nullptr;
	delete uibom_;
	uibom_ = nullptr;*/

	/*delete uititle_;
	uititle_ = nullptr;*/
}

//
//	@brief						初期化
//	@param (m_hWnd)				ウィンドウのハンドル
//	@param (m_pDevice)			デバイス
//	@param (m_pDeviceContext)	デバイスコンテキスト
void Main_Scene::Init(/*HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext*/)
{
	//wnd_ = m_hWnd;
	//device_ = m_pDevice;
	//deviceContext_ = m_pDeviceContext;
	//
	////Direct3Dとシェーダーの初期化
	//STATICMESH::CD3DXMESH::InitDx9();

	////読み込むXファイルの情報を読み込む
	//xfileRead = new XFileRead;
	//xfileRead->ReadXFilePath();

	//読み込みパラメータデータの情報を読み込む
	//parameter = new ParameterRead;
	//parameter->SetJobParameter("./ReadData/JobParameterData.csv");
	//JobParameter* job = parameter->GetJobParamList("剣士");

	//モーションデータの読み込み
	//motionRead_ = new MotionRead;
	//motionRead_->PlayerMotionRead();

	//ステージのファイル読み込み
	//xfile = xfileRead->GetXFile("ステージ5");
	//stage_->Read(xfileRead->GetStageFile(),"ステージ5");
	stage_->Init("ステージ5");

	//スポーンの設定
	//xfile = xfileRead->GetXFile("スポーン");
	spawnManager_->Init("スポーン");
	/*spawnAmount_ = 1;
	spawn_ = new Spawn;
	spawn_->SpawnInit(xfile->GetFileName());*/

	//仮キャラファイル読み込み
	//char name[80];
	//memset(name, 0, sizeof(name));
	//xfile = xfileRead->GetXFile("剣士");
	//memcpy(name, virChar_[Player1]->CharaInit(xfile->GetFileName()), sizeof(name));
	//virChar_[Player1]->CreateFromX(xfile->GetFilePath());
	//virChar_[Player1]->SetParameter(parameter->GetJobParamList("剣士"));
	//virChar_[Player1]->SetMotionData(motionRead_->GetMotionUser("剣士"));
	//virChar_[Player1]->m_Pos = D3DXVECTOR3(-3, 0, -10);
	virChar_[Player1]->CharaInit("剣士");
	virChar_[Player1]->m_Pos = D3DXVECTOR3(0, 0, 0);

	//char name2[80];
	//memset(name2, 0, sizeof(name2));
	//xfile = xfileRead->GetXFile("盾士");
	//memcpy(name2, virChar_[Player2]->CharaInit(xfile->GetFileName()), sizeof(name2));
	//virChar_[Player2]->CreateFromX(xfile->GetFilePath());
	//virChar_[Player2]->CharaInit(xfile->GetFileName());
	//virChar_[Player2]->SetParameter(parameter->GetJobParamList("盾士"));
	//virChar_[Player2]->SetMotionData(motionRead_->GetMotionUser("盾士"));
	virChar_[Player2]->CharaInit("盾士");
	virChar_[Player2]->m_Pos = D3DXVECTOR3(-1.5, 0, -10);

	//char name3[80];
	//memset(name3, 0, sizeof(name3));
	//xfile = xfileRead->GetXFile("魔導士");
	//memcpy(name3, virChar_[Player3]->CharaInit(xfile->GetFileName()), sizeof(name3));
	//virChar_[Player3]->CreateFromX(xfile->GetFilePath());
	//virChar_[Player3]->CharaInit(xfile->GetFileName());
	//virChar_[Player3]->SetParameter(parameter->GetJobParamList("魔導士"));
	//virChar_[Player3]->SetMotionData(motionRead_->GetMotionUser("魔導士"));
	virChar_[Player3]->CharaInit("爆弾士");
	virChar_[Player3]->m_Pos = D3DXVECTOR3(1.5, 0, -10);

	//char name4[80];
	//memset(name4, 0, sizeof(name4));
	//xfile = xfileRead->GetXFile("爆弾士");
	//memcpy(name4, virChar_[Player4]->CharaInit(xfile->GetFileName()), sizeof(name4));
	//virChar_[Player4]->CreateFromX(xfile->GetFilePath());
	//virChar_[Player4]->CharaInit(xfile->GetFileName());
	//virChar_[Player4]->SetParameter(parameter->GetJobParamList("爆弾士"));
	//virChar_[Player4]->SetMotionData(motionRead_->GetMotionUser("爆弾士"));
	virChar_[Player4]->CharaInit("魔導士");
	virChar_[Player4]->m_Pos = D3DXVECTOR3(3, 0, -10);

	//char name5[80];
	//memset(name5, 0, sizeof(name5));
	//xfile = xfileRead->GetXFile("姫");
	//memcpy(name5, princess_->CharaInit(xfile->GetFileName()), sizeof(name5));
	//princess_->CreateFromX(xfile->GetFilePath());
	//princess_->CharaInit(xfile->GetFileName());
	//princess_->SetMotionData(motionRead_->GetMotionUser("姫"));
	princess_->CharaInit("姫");
	princess_->m_Pos = D3DXVECTOR3(0, 0, -12);
	princess_->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
	princess_->SetSpawn(spawnManager_->GetSpawnList());



	//エネミーの読み込み
	//parameter->SetEnemyParameter("./ReadData/EnemyParameterData.csv");

	//char name6[80];
	//memset(name6, 0, sizeof(name6));
	//xfile = xfileRead->GetXFile("スライム");
	//virEnemy_ = new Slim;
	//memcpy(name6, virEnemy_->CharaInit(xfile->GetFileName()), sizeof(name6));
	//slime_->CreateFromX(xfile->GetFilePath());
	//virEnemy_->CharaInit(name);
	time_ = 0;

	//EffectInit(m_pDeviceContext);

	//Title_UI["TITLE_UI"]->Init(L"./UI/UI_Tex/title.png", 0, D3DXVECTOR2(500, 250), D3DXVECTOR2(1024, 512), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));

	//データの解放
	/*delete xfile;
	xfile = nullptr;
	delete parameter;
	parameter = nullptr;*/

}

//
//	@brief	解放
void Main_Scene::Destroy()
{
}

////
////	@brief	デバッグ用初期化
//HRESULT Main_Scene::DebugInit(ID3D11DeviceContext* m_pDeviceContext)
//{
//	debugText_ = new D3D11_TEXT;
//	ID3D11DeviceContext* deviceContext_ = m_pDeviceContext;
//	D3DXVECTOR4 vColor(0, 0, 0, 1);
//	if (FAILED(debugText_->Init(deviceContext_, WINDOW_WIDTH, WINDOW_HEIGHT, 100, vColor)))
//	{
//		return E_FAIL;
//	}
//	return S_OK;
//}

//HRESULT Main_Scene::EffectInit(ID3D11DeviceContext* m_pDeviceContext)
//{
//	
//	deviceContext_ = m_pDeviceContext;
//	float scaleF = 8;
//	D3DXVECTOR3 scale(scaleF, 5, scaleF);
//
//	uititle_ = new D3D11_SPRITE;
//	//パス、透過フラグ、レクトサイズ、スピード、スケール（等倍）	
//	if (FAILED(uititle_->CreateEffects(L"./Effect/Effect_Tex/title.png", true, D3DXVECTOR2(1, 1), 1,D3DXVECTOR3(20,20,20))))
//	{
//		return E_FAIL;
//	}
//
//	uisword_ = new D3D11_SPRITE;
//	//パス、透過フラグ、レクトサイズ、スピード、スケール（等倍）	
//	if (FAILED(uisword_->CreateEffects(L"./Effect/Effect_Tex/UISword.png", true, D3DXVECTOR2(1, 1), 5, scale)))
//	{
//		return E_FAIL;
//	}
//	uiseeld_ = new D3D11_SPRITE;
//	//パス、透過フラグ、レクトサイズ、スピード、スケール（等倍）	
//	if (FAILED(uiseeld_->CreateEffects(L"./Effect/Effect_Tex/UISeeld.png", true, D3DXVECTOR2(1, 1), 5, scale)))
//	{
//		return E_FAIL;
//	}
//	uimagic_ = new D3D11_SPRITE;
//	//パス、透過フラグ、レクトサイズ、スピード、スケール（等倍）	
//	if (FAILED(uimagic_->CreateEffects(L"./Effect/Effect_Tex/UIMagic.png", true, D3DXVECTOR2(1, 1), 5, scale)))
//	{
//		return E_FAIL;
//	}
//	uibom_ = new D3D11_SPRITE;
//	//パス、透過フラグ、レクトサイズ、スピード、スケール（等倍）	
//	if (FAILED(uibom_->CreateEffects(L"./Effect/Effect_Tex/UIBom.png", true, D3DXVECTOR2(1, 1), 5, scale)))
//	{
//		return E_FAIL;
//	}
//
//	
//
//	return S_OK;
//}

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
	default:
		break;
	}

	//リセット処理(デバッグ用)
	if (GetKeyState('R') & 0x80)
	{
		for (auto c : charList_)
		{
			c->Reset();
		}
		enemyList_.clear();
		charList_.clear();

		for (int i = 0; i < 4; i++)
		{
			charList_.push_back(virChar_[i]);
		}
		charList_.push_back(princess_);
		spawnManager_->Reset();

		princess_->SetSpawn(spawnManager_->GetSpawnList());
	}

	//camera_->Update(princess_->m_Pos);
}

//
//	@brief	シーン遷移更新
SceneBase* Main_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;

	Update();

	if (GetKeyState(VK_F3) & 0x80)
	{
		next = new Title_Scene;
	}

	return next;
}

//
//	@brief	ゲーム開始
void Main_Scene::GameStart()
{
	//int count = 5;
	//if (++time_ % (FPS * count) == 0)
	//{
	//	scene_ = MainS;
	//}
	spawnFlg_ = false;
	if (GetKeyState(VK_RETURN) & 0x80)
	{
		scene_ = MainS;
		Sound::getInstance().BGM_play("SENTOU");

	}
}

//
//	@brief	ゲームメイン
void Main_Scene::GameMain()
{

	//デバッグ用
	if (GetKeyState('E') & 0x80)
	{
		scene_ = EndS;
	}
	if (GetKeyState('S') & 0x80)
	{
		spawnFlg_ = true;
	}

	////エネミースポーン処理
	if (spawnFlg_ == true)
	{
		if (enemyList_.size() < 50)
		{
			//spawnManager_->Update(parameter, princess_);
			std::vector<EnemyJobManager*> temp = spawnManager_->OutEnemy();
			if (!temp.empty())
			{
				for (auto e : temp)
				{
					enemyList_.push_back(e);
					charList_.push_back(e);
				}
				temp.clear();
			}
		}


		//エネミーターゲット更新
		if (!enemyList_.empty())
		{
			for (auto enemy : enemyList_)
			{
				//プレイヤーループ
				for (int i = 0; i < 4; i++)
				{
					enemy->Target_Update(virChar_[i], princess_);
				}
			}
		}
	}

	//キャラ更新
	for (auto chara : charList_)
	{
		chara->CharaUpdate();
		chara->SetAllCharaList(charList_);
	}

	//姫の目的地更新
	D3DXVECTOR3 pos = princess_->m_Pos;
	CharaType no = PrincessT;
	double timing = 0;
	for (int i = 0; i < 4; i++)
	{
		if (timing < virChar_[i]->GetCallTiming())
		{
			timing = virChar_[i]->GetCallTiming();
			no = virChar_[i]->GetCharaType();
		}
	}
	if (no != PrincessT)
	{
		pos = virChar_[no]->GetCallPos();
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
		if (!virChar_[i]->GetAliveFlg())
		{
			princess_->SetDeadCharaList(virChar_[i]);
			++deadCount;
		}
	}

	//ゲーム終了(姫死亡 又は プレイヤー全滅 又はクリア)
	if (!(princess_->GetAliveFlg() || deadCount == 4))
	{
		scene_ = EndS;
	}
}

//
//	@brief	ゲーム終了
void Main_Scene::GameEnd()
{
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		scene_ = StartS;

		princess_->SetSpawn(spawnManager_->GetSpawnList());

		for (auto c : charList_)
		{
			c->Reset();
		}
		enemyList_.clear();
		charList_.clear();

		for (int i = 0; i < 4; i++)
		{
			charList_.push_back(virChar_[i]);
		}
		charList_.push_back(princess_);
		spawnManager_->Reset();

		princess_->SetSpawn(spawnManager_->GetSpawnList());
	}
}

//
//	@brief	エネミー死亡処理
void Main_Scene::EnemyDestroy()
{
	if (!enemyList_.empty())
	{
		for (auto c : enemyList_)
		{
			if (!c->GetAliveFlg())
			{
				killList_.push_back(c);
			}
		}
	}

	if (!killList_.empty())
	{
		for (auto c : killList_)
		{
			//キャラリストから探す
			auto cl = std::find(std::begin(charList_), std::end(charList_), c);

			//エネミーリストから探す
			auto el = std::find(std::begin(enemyList_), std::end(enemyList_), c);

			//　オブジェクトの終了処理
			delete (*cl);
			//	リストから外す
			charList_.erase(cl);
			enemyList_.erase(el);
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
	//bool wallFlg = false;
	for (auto chara : charList_)
	{
		if (chara->m_Dir != D3DXVECTOR3(0,0,0))
		{
			if (ray_->RayIntersect(chara, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.3)
			{
				if (chara->GetKnockBackFlg() == true)
				{
					chara->SetKnockBackFlg(false);
				}

				//当たり状態なので、滑らせる
				chara->SlipMove(ray_->Slip(chara->m_Dir, vNormal));
				//滑りベクトル先の壁とのレイ判定 ２重に判定	
				if (ray_->RayIntersect(chara, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.2)
				{
					chara->StopMove();
				}
			}
		}

	}

	//周辺にキャラクターがいるかどうか
	for (int i = 0; i < charList_.size(); i++)
	{
		for (int j = i + 1; j < charList_.size(); j++)
		{
			if (ray_->CheckSpaceNo(charList_[i]->GetSpaceNo(), charList_[j]->GetSpaceNo()))
			{
				charList_[i]->SetAroundChara(charList_[j]);
				charList_[j]->SetAroundChara(charList_[i]);
			}
		}
	}
}

//
//	@brief			描画
//	@param (mView)	描画用マトリックス
//	@param (mProj)	射影変換用マトリックス
void Main_Scene::Render(/*D3DXMATRIX mView, D3DXMATRIX mProj*/)
{
	//D3DXMATRIX mView = camera_->GetView();
	//D3DXMATRIX mProj = camera_->GetProj();

	//virEnemy_->Render(D3DXVECTOR3(0, 0, 0));
	//virEnemy_->Render(D3DXVECTOR3(1, 0, 0));

	//ステージの描画
	stage_->Render();

	//スポーンゲートの描画
	spawnManager_->Render();

	//EffectRender();

	//virEnemy_->CharaRender(mView, mProj);

	//仮キャラ描画
	/*for (int i = 0; i < 4; i++)
	{
		virChar_[i]->CharaRender(mView, mProj);
	}*/

	if (!enemyList_.empty())
	{
		for (auto enemy : enemyList_)
		{
			slime_->Render(enemy->m_Pos, enemy->m_Yaw, enemy->m_Scale);
		}
	}

	for (auto chara : charList_)
	{
		if (chara->GetCharaType() != Enemy)
		{
			chara->CharaRender();
		}
	}

	//if (spawn_ != nullptr)
	//{
	//	//for (int i = 0; i < spawnAmount_; i++)
	//	//{
	//	if (spawn_ != nullptr)
	//	{
	//		//spawn_->SpawnRender();
	//	}
	//	//}
	//}

	PlayerDebug();
#ifdef _DEBUG
	//EnemyDebug();
#endif // _DEBUG


	camera_->Render();

	//char str[256];
	//sprintf(str, "%f",camera_->GetDist());
	//debugText_->Render(str, 0, 10);
	//sprintf(str, "zoom : %f", virChar_[Player2]->m_Pos.x);
	//debugText_->Render(str, 0, 30);
	//sprintf(str, "y : %f",camera_->GetPos().y);
	//debugText_->Render(str, 0, 50);
}

//void Main_Scene::EffectRender()
//{
//	static float x = 0;
//	D3DXMATRIX Tran, World, World2;
//	//ビルボードのワールドトランスフォーム	
//	x = 0;
//	D3DXMatrixTranslation(&Tran, x, 10, 0);
//	World = Tran;
//	World2 = Tran;
//	D3DXMATRIX CancelRotation = Camera::mView_;
//	CancelRotation._41 = CancelRotation._42 = CancelRotation._43 = 0;
//	D3DXMatrixInverse(&CancelRotation, NULL, &CancelRotation);
//	World2 = CancelRotation * World2;
//	
//	//Title_UI["TITLE_UI"]->Render(0, 0, 0, 0);
//
//	if (scene_ != MainS)
//	{
//		//Title_UI["TITLE_UI"]->Render(0, 0, 0, 0);
//	}
//	else
//	{
//		/*float high = -28;
//		uisword_->RenderSprite(World2, D3DXVECTOR3(-18, 0, high));
//		uiseeld_->RenderSprite(World2, D3DXVECTOR3(-8.5, 0, high));
//		uimagic_->RenderSprite(World2, D3DXVECTOR3(0.5, 0, high));
//		uibom_->RenderSprite(World2, D3DXVECTOR3(10, 0, high));*/
//	}
//	
//}

//SceneBase * Main_Scene::Update(SceneRoot * root)
//{
//	//std::cout << "SceneMain::Update()" << std::endl;
//	SceneBase* next = this;
//
//	//
//	//	process...
//	//
//	switch (getchar())
//	{
//	case SceneRoot::kTitle:
//		next = new SceneTitle();
//		break;
//	default:
//		break;
//	}
//
//	return next;
//}

void Main_Scene::PlayerDebug()
{
	//デバッグ描画
	char str[256];
	
	
#ifdef _DEBUG
	sprintf(str, "chara:%d", virChar_[Player1]->GetAroundC());
	debugText_->Render(str, 0, 50);
#endif // _DEBUG


	if(scene_ == MainS)
	{
		float high = 960;
		sprintf(str, "%f  %f  %f", virChar_[Player1]->m_Pos.x, virChar_[Player1]->m_Pos.y, virChar_[Player1]->m_Pos.z);
		debugText_->Render(str, 248, high);
		/*sprintf(str, "%d", virChar_[Player2]->m_Pos);
		debugText_->Render(str, 760, high);
		sprintf(str, "%d", virChar_[Player3]->m_Pos);
		debugText_->Render(str, 1240, high);
		sprintf(str, "%d", virChar_[Player4]->m_Pos);
		debugText_->Render(str, 1740, high);*/
	}
	
	
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