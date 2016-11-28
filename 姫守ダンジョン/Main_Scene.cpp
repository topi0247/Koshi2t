//
//	@file	Main_Scene.cpp
//	@brief	ゲームメインシーン管理
//	@date	2016/11/08
//	@outher	仁科香苗

#include "Main_Scene.h"

//
//	@brief	コンストラクタ
Main_Scene::Main_Scene()
{
	stage_ = new Stage;
	virChar_ = new JobManager *[4];
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

	slime_ = new CD3DXSKINMESH;
	//virEnemy_ = new Slim;

	camera_ = new Camera;
}

//
//	@brief	デストラクタ
Main_Scene::~Main_Scene()
{
	delete stage_;
	stage_ = nullptr;

	if (spawn_ != nullptr)
	{
		delete spawn_;
		spawn_ = nullptr;
	}

	//delete ray_;
	//ray_ = nullptr;

	for (int i = 0; i < 4; i++)
	{
		delete virChar_[i];
		virChar_[i] = nullptr;
	}
	delete[] virChar_;
	virChar_ = nullptr;

	delete princess_;
	princess_ = nullptr;


	//for (auto chara : charList_)
	//{
	//	delete chara;
	//	chara = nullptr;
	//}
	//for (int i = 0; i < 10; i++)
	//{
	//delete virEnemy_;
	//virEnemy_ = nullptr;
	//}
	delete virEnemy_;
	virEnemy_ = nullptr;

	delete slime_;
	slime_ = nullptr;

	delete debugText_;
	debugText_ = nullptr;

	delete xfile;
	xfile = nullptr;
	delete parameter;
	parameter = nullptr;

	delete camera_;
	camera_ = nullptr;
}

//
//	@brief						初期化
//	@param (m_hWnd)				ウィンドウのハンドル
//	@param (m_pDevice)			デバイス
//	@param (m_pDeviceContext)	デバイスコンテキスト
void Main_Scene::Init(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext)
{
	wnd_ = m_hWnd;
	device_ = m_pDevice;
	//deviceContext_ = m_pDeviceContext;
	//
	////Direct3Dとシェーダーの初期化
	//STATICMESH::CD3DXMESH::InitDx9();

	//読み込むXファイルの情報を読み込む
	xfileRead = new XFileRead;
	xfileRead->ReadXFilePath();

	//読み込みパラメータデータの情報を読み込む
	parameter = new ParameterRead;
	parameter->SetJobParameter("./ReadData/JobParameterData.csv");
	//JobParameter* job = parameter->GetJobParamList("剣士");

	//モーションデータの読み込み
	motionRead_ = new MotionRead;
	motionRead_->PlayerMotionRead();

	//ステージのファイル読み込み
	xfile = xfileRead->GetXFile("ステージ5");
	stage_->Read(xfile->GetFileName());

	//スポーンの設定
	xfile = xfileRead->GetXFile("スポーン1");
	spawnAmount_ = 1;
	spawn_ = new Spawn;
	spawn_->SpawnInit(xfile->GetFileName());

	//仮キャラファイル読み込み
	char name[80];
	memset(name, 0, sizeof(name));
	xfile = xfileRead->GetXFile("剣士");
	memcpy(name, virChar_[Player1]->CharaInit(xfile->GetFileName()), sizeof(name));
	virChar_[Player1]->CreateFromX(name);
	virChar_[Player1]->SetParameter(parameter->GetJobParamList("剣士"));
	virChar_[Player1]->SetMotionData(motionRead_->GetMotionUser("剣士"));
	virChar_[Player1]->m_Pos = D3DXVECTOR3(-3, 0, -10);

	memset(name, 0, sizeof(name));
	xfile = xfileRead->GetXFile("盾士");
	memcpy(name, virChar_[Player2]->CharaInit(xfile->GetFileName()), sizeof(name));
	virChar_[Player2]->CreateFromX(name);
	//virChar_[Player2]->CharaInit(xfile->GetFileName());
	virChar_[Player2]->SetParameter(parameter->GetJobParamList("盾士"));
	virChar_[Player2]->SetMotionData(motionRead_->GetMotionUser("盾士"));
	virChar_[Player2]->m_Pos = D3DXVECTOR3(-1.5, 0, -10);

	memset(name, 0, sizeof(name));
	xfile = xfileRead->GetXFile("魔導士");
	memcpy(name, virChar_[Player3]->CharaInit(xfile->GetFileName()), sizeof(name));
	virChar_[Player3]->CreateFromX(name);
	//virChar_[Player3]->CharaInit(xfile->GetFileName());
	virChar_[Player3]->SetParameter(parameter->GetJobParamList("魔導士"));
	virChar_[Player3]->SetMotionData(motionRead_->GetMotionUser("魔導士"));
	virChar_[Player3]->m_Pos = D3DXVECTOR3(1.5, 0, -10);



	memset(name, 0, sizeof(name));
	xfile = xfileRead->GetXFile("爆弾士");
	memcpy(name, virChar_[Player4]->CharaInit(xfile->GetFileName()), sizeof(name));
	virChar_[Player4]->CreateFromX(name);
	//virChar_[Player4]->CharaInit(xfile->GetFileName());
	virChar_[Player4]->SetParameter(parameter->GetJobParamList("爆弾士"));
	virChar_[Player4]->SetMotionData(motionRead_->GetMotionUser("爆弾士"));
	virChar_[Player4]->m_Pos = D3DXVECTOR3(3, 0, -10);

	memset(name, 0, sizeof(name));
	xfile = xfileRead->GetXFile("姫");
	memcpy(name, princess_->CharaInit(xfile->GetFileName()), sizeof(name));
	princess_->CreateFromX(name);
	//princess_->CharaInit(xfile->GetFileName());
	princess_->SetMotionData(motionRead_->GetMotionUser("姫"));
	princess_->m_Pos = D3DXVECTOR3(0, 0, -12);
	princess_->SetSpawn(spawn_);



	//エネミーの読み込み
	parameter->SetEnemyParameter("./ReadData/EnemyParameterData.csv");

	memset(name, 0, sizeof(name));
	xfile = xfileRead->GetXFile("スライム");
	virEnemy_ = new Slim;
	memcpy(name, virEnemy_->CharaInit(xfile->GetFileName()), sizeof(name));
	slime_->CreateFromX(name);
	//virEnemy_->CharaInit(name);
	time_ = 0;


	//データの解放
	/*delete xfile;
	xfile = nullptr;
	delete parameter;
	parameter = nullptr;*/

}

//
//	@brief	デバッグ用初期化
HRESULT Main_Scene::DebugInit(ID3D11DeviceContext* m_pDeviceContext)
{
	debugText_ = new D3D11_TEXT;
	deviceContext_ = m_pDeviceContext;
	D3DXVECTOR4 vColor(1, 1, 1, 1);
	if (FAILED(debugText_->Init(deviceContext_, WINDOW_WIDTH, WINDOW_HEIGHT, 100, vColor)))
	{
		return E_FAIL;
	}
	return S_OK;
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
	default:
		break;
	}

	//カメラの更新
	for (int i = 0; i < 4; i++)
	{
		camera_->SetPlayerPos(virChar_[i]->m_Pos);
	}
	camera_->Update();
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

	if (GetKeyState(VK_RETURN) & 0x80)
	{
		scene_ = MainS;
	}
}

//
//	@brief	ゲームメイン
void Main_Scene::GameMain()
{
	//エネミースポーン処理
	//if (++time_ % (FPS * 3) == 0 && spawn_!=nullptr)
	//{
	//	spawn_->ListSet(parameter, princess_);
	//	std::vector<EnemyJobManager*> temp = spawn_->EnemySpawn();
	//	for (auto e : temp)
	//	{
	//		enemyList_.push_back(e);
	//		charList_.push_back(e);
	//	}
	//	spawn_->ListReset();
	//	temp.clear();
	//	//for (int i = 0; i < 5; i++)
	//	//{
	//		//virEnemy_->m_Pos.x += i;
	//	//virEnemy_ = new Slim;
	//	//virEnemy_->SetParameter(parameter->GetEnemyParamList("スライム"));
	//	//virEnemy_->SetTarget(princess_);
	//	//virEnemy_->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
	//	////virEnemy_->m_Pos = D3DXVECTOR3(0, 0, 0);
	//	//enemyList_.push_back(virEnemy_);
	//	//charList_.push_back(virEnemy_);
	//	//}
	//}



	//エネミーターゲット更新
	if (!enemyList_.empty())
	{
		for (auto enemy : enemyList_)
		{
			//プレイヤーループ
			for (int i = 0; i < 4; i++)
			{
				//プレイヤーとエネミーが一定の距離内
				float dist = 5.0;
				if (ray_->CharaNear(enemy->m_Pos, virChar_[i]->m_Pos, dist))
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

	if (princess_->SealSpawn() != nullptr)
	{
		delete spawn_;
		spawn_ = nullptr;
	}


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

			//　オブジェクトの終了処理
			//delete (*el);
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
		if (ray_->RayIntersect(chara, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.3)
		{
			//当たり状態なので、滑らせる
			//virChar_[player1]->m_Pos = ray_->Slip(virChar_[player1]->m_Dir, vNormal);//滑りベクトルを計算
			chara->SlipMove(ray_->Slip(chara->m_Dir, vNormal));
			//滑りベクトル先の壁とのレイ判定 ２重に判定	
			if (ray_->RayIntersect(chara, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.2)
			{
				//virChar_[player1]->m_Pos = D3DXVECTOR3(0, 0, 0);//止める
				chara->StopMove();
				//wallFlg = true;
			}
		}
		//周辺にキャラクターがいるかどうかの確認
		for (auto opp : charList_)
		{
			if (chara != opp)
			{
				//charaとoppの距離を判定

				//近かったら
				chara->SetAroundChara(opp);
				opp->SetAroundChara(chara);
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

	if (spawn_ != nullptr)
	{
		//for (int i = 0; i < spawnAmount_; i++)
		//{
			if (spawn_ != nullptr)
			{
				spawn_->SpawnRender();
			}
		//}
	}

	//PlayerDebug();
	//EnemyDebug();

	camera_->Render();

	//char str[256];
	//sprintf(str, "%f",camera_->GetDist());
	//debugText_->Render(str, 0, 10);
	//sprintf(str, "zoom : %f", virChar_[Player2]->m_Pos.x);
	//debugText_->Render(str, 0, 30);
	//sprintf(str, "y : %f",camera_->GetPos().y);
	//debugText_->Render(str, 0, 50);
}

void Main_Scene::PlayerDebug()
{
	//デバッグ描画
	char str[256];
	sprintf(str, "Atk(no0,w1,na2,c3,sa4) : %d", virChar_[Player2]->GetAtkState());
	debugText_->Render(str, 0, 10);
	//sprintf(str, "alive : %d", virChar_[Player2]->GetAliveFlg());
	//debugText_->Render(str, 0, 10);
	sprintf(str, "motionNo : %d", virChar_[Player2]->GetMotionNo());
	debugText_->Render(str, 0, 30);
	sprintf(str, "motionSPeed : %f", virChar_[Player2]->GetMotionSpeed());
	debugText_->Render(str, 0, 50);
	sprintf(str, "motionCount : %d", virChar_[Player2]->GetMotionCount());
	debugText_->Render(str, 0, 70);
	sprintf(str, "def_ : %d", virChar_[Player2]->GetParam()->def_);
	debugText_->Render(str, 0, 90);
	sprintf(str, "specialAttackTime_ : %f", virChar_[Player2]->GetParam()->specialAttackTime_);
	debugText_->Render(str, 0, 110);
	sprintf(str, "chargeTime_ : %d", virChar_[Player2]->GetParam()->chargeTime_);
	debugText_->Render(str, 0, 130);
	sprintf(str, "moveSpeed_ : %f", virChar_[Player2]->GetParam()->moveSpeed_);
	debugText_->Render(str, 0, 150);
	sprintf(str, "specialMoveSpeed_ : %f", virChar_[Player2]->GetParam()->specialMoveSpeed_);
	debugText_->Render(str, 0, 170);
	sprintf(str, "weight_ : %f", virChar_[Player2]->GetParam()->weight_);
	debugText_->Render(str, 0, 190);
	sprintf(str, "attackReach_ : %f", virChar_[Player2]->GetParam()->attackReach_);
	debugText_->Render(str, 0, 210);
	sprintf(str, "attackRange_ : %f", virChar_[Player2]->GetParam()->attackRange_);
	debugText_->Render(str, 0, 230);
	sprintf(str, "scale_ : %f", virChar_[Player2]->GetParam()->scale_);
	debugText_->Render(str, 0, 250);
	sprintf(str, "x : %f y :%f", virChar_[Player2]->m_Pos.x, virChar_[Player2]->m_Pos.z);
	debugText_->Render(str, 0, 270);
}

void Main_Scene::EnemyDebug()
{
	char str[256];
	if (!enemyList_.empty())
	{
		//EnemyJobManager* obj = enemyList_[0];
		sprintf(str, "count : %d", enemyList_.size());
		debugText_->Render(str, 0, 10);
		/*sprintf(str, "alive : %d", obj->GetAliveFlg());
		debugText_->Render(str, 0, 10);
		sprintf(str, "hp_ : %d", obj->GetHP());
		debugText_->Render(str, 0, 30);
		sprintf(str, "atk_ : %d", obj->GetParam()->atk_);
		debugText_->Render(str, 0, 50);
		sprintf(str, "reach : %d", obj->GetParam()->attackReach_);
		debugText_->Render(str, 0, 70);
		sprintf(str, "def_ : %d", obj->GetParam()->def_);
		debugText_->Render(str, 0, 90);
		sprintf(str, "moveSpeed: %f", obj->GetParam()->moveSpeed_);
		debugText_->Render(str, 0, 110);
		sprintf(str, "targetAlive: %d", obj->GetTarget()->GetAliveFlg());
		debugText_->Render(str, 0, 130);
		sprintf(str, "targetType: %d", obj->GetTarget()->GetCharaType());
		debugText_->Render(str, 0, 150);
		sprintf(str, "count : %d", enemyList_.size());
		debugText_->Render(str, 0, 350);
		sprintf(str, "ins : %f", insTime_);
		debugText_->Render(str, 0, 370);
		sprintf(str, "push : %f", pushTime_);
		debugText_->Render(str, 0, 390);*/
	}
}