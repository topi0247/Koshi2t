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
	virChar_[player1] = new SwordMan(Controller::player1,CharaType::Player1);
	virChar_[player2] = new Witch(Controller::player2, CharaType::Player2);
	virChar_[player3] = new ShieldMan(Controller::player3, CharaType::Player3);
	virChar_[player4] = new Bomber(Controller::player4, CharaType::Player4);

	for (int i = 0; i < 4; i++)
	{
		charList_.push_back(virChar_[i]);
	}


	/*virEnemy_ = new Slim;*/
	virEnemy_ = new EnemyJobManager*[10];
	for (int i = 0; i < 10;i++)
	{
		virEnemy_[i] = new Slim;
		//enemyList_.push_back(virEnemy_[i]);
	}
	ray_ = new Collision;

	//charList_.push_back(virEnemy_[0]);
}

//
//	@brief	デストラクタ
Main_Scene::~Main_Scene()
{
	delete stage_;
	stage_ = nullptr;

	delete ray_;
	ray_ = nullptr;
	
	for (int i = 0; i < 4; i++)
	{
		delete virChar_[i];
		virChar_[i] = nullptr;
	}
	delete[] virChar_;
	virChar_ = nullptr;

	//for (auto chara : charList_)
	//{
	//	delete chara;
	//	chara = nullptr;
	//}
	for (int i = 0; i < 10; i++)
	{
		delete virEnemy_[i];
		virEnemy_[i] = nullptr;
	}
	delete[] virEnemy_;
	virEnemy_ = nullptr;
	

	delete debugText_;
	debugText_ = nullptr;
}

//
//	@brief						初期化
//	@param (m_hWnd)				ウィンドウのハンドル
//	@param (m_pDevice)			デバイス
//	@param (m_pDeviceContext)	デバイスコンテキスト
void Main_Scene::Init(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext)
{
	//読み込むXファイルの情報を読み込む
	XFileRead* xfileRead = new XFileRead;
	xfileRead->ReadXFilePath();

	//ステージのファイル読み込み
	XFile* xfile = xfileRead->GetXFile("ステージ1_floor1");
	XFile* xfile2= xfileRead->GetXFile("ステージ1_wall1");
	stage_->Read(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName(),xfile2->GetFileName());

	//仮キャラファイル読み込み
	xfile = xfileRead->GetXFile("剣士");
	virChar_[player1]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[player1]->m_vPos = D3DXVECTOR3(26, 0, 11);

	xfile = xfileRead->GetXFile("魔導士");
	virChar_[player2]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[player2]->m_vPos = D3DXVECTOR3(20, 0, -11);

	xfile = xfileRead->GetXFile("盾士");
	virChar_[player3]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[player3]->m_vPos = D3DXVECTOR3(-26, 0, 11);

	xfile = xfileRead->GetXFile("爆弾士");
	virChar_[player4]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[player4]->m_vPos = D3DXVECTOR3(-20, 0, -11);

	xfile = xfileRead->GetXFile("スライム");
	for (int i = 0; i < 10; i++)
	{
		virEnemy_[i]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	}

	/*for (auto enemy : enemyList_)
	{
		enemy->SetTarget(virChar_[4]);
	}*/
}

//
//	@brief	デバッグ用初期化
HRESULT Main_Scene::DebugInit(ID3D11DeviceContext* m_pDeviceContext)
{
	debugText_ = new D3D11_TEXT;
	D3DXVECTOR4 vColor(1, 1, 1, 1);
	if (FAILED(debugText_->Init(m_pDeviceContext, WINDOW_WIDTH, WINDOW_HEIGHT, 100, vColor)))
	{
		return E_FAIL;
	}
	return S_OK;
}

//
//	@brief	更新
void Main_Scene::Update()
{
	//エネミースポーン処理
	static int enemyCount = 0;
	if ((GetKeyState(VK_F1) & 0x80) && enemyCount<10)
	{
		charList_.push_back(virEnemy_[enemyCount]);
		enemyList_.push_back(virEnemy_[enemyCount]);
		enemyList_[enemyCount]->SetTarget(virChar_[player4]);
		++enemyCount;
		//for (auto enemy : enemyList_)
		//{
		//	enemy->SetTarget(virChar_[4]);
		//}
	}



	/*for (int i = 0; i < 3; i++)
	{
		virEnemy_[0]->SetTargetChar(virChar_[i], virChar_[player4]);
	}*/
	if(!enemyList_.empty())
	for (auto enemy : enemyList_)
	{
		//プレイヤーループ
		//for (int i = 0; i < 4; i++)
		//{
			//プレイヤーとエネミーが一定の距離内
			float dist = 5.0;
			if (ray_->CharaNear(enemy->m_vPos, virChar_[player1]->m_vPos, dist))
			{
				enemy->Target_Update(virChar_[player1], virChar_[player4]);
			}
		//}
	}
	//virEnemy_[0]->CharaUpdate();



	//virEnemy_[0]->CheckNearPlayer(virChar_[player1]->m_vPos);
	//virEnemy_[0]->CharaUpdate();



	//ray_->CharaNear(virChar_[player1]->m_vPos, virEnemy_[0]->m_vPos, 50.0);

	//仮キャラ更新
	for (auto chara : charList_)
	{
		chara->CharaUpdate();
	}

	//衝突判定の更新
	CollisionControl();

	//キャラの移動更新
	for (auto chara : charList_)
	{
		chara->Move_Update();
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
		if (ray_->RayIntersect(chara, stage_->GetMeshWallInfo(), &fDistance, &vNormal) && fDistance <= 0.3)
		{
			//当たり状態なので、滑らせる
			//virChar_[player1]->m_vPos = ray_->Slip(virChar_[player1]->m_Dir, vNormal);//滑りベクトルを計算
			chara->SlipMove(ray_->Slip(chara->m_Dir, vNormal));
			//滑りベクトル先の壁とのレイ判定 ２重に判定	
			if (ray_->RayIntersect(chara, stage_->GetMeshWallInfo(), &fDistance, &vNormal) && fDistance <= 0.2)
			{
				//virChar_[player1]->m_vPos = D3DXVECTOR3(0, 0, 0);//止める
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
void Main_Scene::Render(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	//ステージの描画
	stage_->Render(mView, mProj);

	//virEnemy_->CharaRender(mView, mProj);

	//仮キャラ描画
	/*for (int i = 0; i < 4; i++)
	{
		virChar_[i]->CharaRender(mView, mProj);
	}*/
	for (auto chara : charList_)
	{
		chara->CharaRender(mView, mProj);
	}

	//デバッグ描画
	char str[256];
	sprintf(str, "Atk(n-1 | s-2) : %d", virChar_[player1]->GetAtkState());
	debugText_->Render(str, 0, 10);
	sprintf(str, "AtkCount : %d", virChar_[player1]->GetAtkCnt());
	debugText_->Render(str, 0, 30);
	sprintf(str, "axis : %f", virChar_[player1]->m_AxisZ.z);
	debugText_->Render(str, 0, 50);
	sprintf(str, "count : %d", enemyList_.size());
	debugText_->Render(str, 0, 70);
	float dist = pow(virEnemy_[0]->m_vPos.x - virChar_[player1]->m_vPos.x, 2) + pow(virEnemy_[0]->m_vPos.z - virChar_[player1]->m_vPos.z, 2);
	sprintf(str, "dist: %f", dist);
	debugText_->Render(str, 0, 90);
	/*sprintf(str, "count : %i", ray_->GetHitCnt());
	debugText_->Render(str, 0, 70);*/
	//sprintf(str, "pos x : %f :pos z : %f", virEnemy_->GetTargetPos().x, virEnemy_->GetTargetPos().z);
	//debugText_->Render(str, 0, 70);
	//sprintf(str, "pos x : %f :pos z : %f", virEnemy_->m_vPos.x, virEnemy_->m_vPos.z);
	//debugText_->Render(str, 0, 90);

}