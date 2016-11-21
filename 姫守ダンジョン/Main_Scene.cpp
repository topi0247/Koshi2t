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
	virChar_[Player2] = new SwordMan(CharaType::Player2);
	virChar_[Player1] = new Witch(CharaType::Player1);
	virChar_[Player3] = new ShieldMan( CharaType::Player3);
	virChar_[Player4] = new Bomber(CharaType::Player4);

	for (int i = 0; i < 4; i++)
	{
		charList_.push_back(virChar_[i]);
	}
	virEnemy_ = new Slim;

	/*virEnemy_ = new Slim;*/
	//virEnemy_ = new EnemyJobManager*[10];
	//for (int i = 0; i < 10;i++)
	//{
		//virEnemy_[i] = new Slim;
		//enemyList_.push_back(virEnemy_[i]);
	//}
	//ray_ = new Collision;

	//charList_.push_back(virEnemy_[0]);
}

//
//	@brief	デストラクタ
Main_Scene::~Main_Scene()
{
	delete stage_;
	stage_ = nullptr;

	//delete ray_;
	//ray_ = nullptr;

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
	//for (int i = 0; i < 10; i++)
	//{
	delete virEnemy_;
	virEnemy_ = nullptr;
	//}
	//delete[] virEnemy_;
	//virEnemy_ = nullptr;


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

	//読み込みパラメータデータの情報を読み込む
	ParameterRead* parameter = new ParameterRead;
	parameter->SetJobParameter("./ReadData/JobParameterData.csv");

	//ステージのファイル読み込み
	XFile* xfile = xfileRead->GetXFile("ステージ0");
	stage_->Read(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName(), xfile->GetFileName());

	//仮キャラファイル読み込み
	xfile = xfileRead->GetXFile("剣士");
	virChar_[Player1]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[Player1]->SetParameter(parameter->GetJobParamList("剣士"));
	virChar_[Player1]->m_Pos = D3DXVECTOR3(10, 0, -10);

	xfile = xfileRead->GetXFile("魔導士");
	virChar_[Player2]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[Player2]->SetParameter(parameter->GetJobParamList("魔導士"));
	virChar_[Player2]->m_Pos = D3DXVECTOR3(5, 0, -10);

	xfile = xfileRead->GetXFile("盾士");
	virChar_[Player3]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[Player3]->SetParameter(parameter->GetJobParamList("盾士"));
	virChar_[Player3]->m_Pos = D3DXVECTOR3(-5, 0, -10);

	xfile = xfileRead->GetXFile("爆弾士");
	virChar_[Player4]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[Player4]->SetParameter(parameter->GetJobParamList("爆弾士"));
	virChar_[Player4]->m_Pos = D3DXVECTOR3(-10, 0, -10);

	xfile = xfileRead->GetXFile("スライム");
	//for (int i = 0; i < 10; i++)
	//{
	virEnemy_->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	//}

	/*for (auto enemy : enemyList_)
	{
		enemy->SetTarget(virChar_[4]);
	}*/
	time_ = 0;


	//データの解放
	delete xfile;
	xfile = nullptr;
	delete parameter;
	parameter = nullptr;

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
	//if ((GetKeyState(VK_F1) & 0x80))
	//{
	/*if (++time_ % (FPS * 3)==0)
	{
		EnemyJobManager* slim = new Slim;
		slim = virEnemy_;
		slim->m_Pos = D3DXVECTOR3(0, 0, 0);
		charList_.push_back(slim);
		enemyList_.push_back(slim);
		enemyList_[enemyCount]->SetTarget(virChar_[player4]);
		++enemyCount;
	}*/
	//for (auto enemy : enemyList_)
	//{
	//	enemy->SetTarget(virChar_[4]);
	//}
//}



/*for (int i = 0; i < 3; i++)
{
	virEnemy_[0]->SetTargetChar(virChar_[i], virChar_[player4]);
}*/
	if (!enemyList_.empty())
	{
		for (auto enemy : enemyList_)
		{
			//プレイヤーループ
			//for (int i = 0; i < 4; i++)
			//{
				//プレイヤーとエネミーが一定の距離内
			float dist = 5.0;
			if (ray_->CharaNear(enemy->m_Pos, virChar_[Player1]->m_Pos, dist))
			{
				enemy->Target_Update(virChar_[Player1], virChar_[Player4]);
			}
			//}
		}
	}
	//virEnemy_[0]->CharaUpdate();



	//virEnemy_[0]->CheckNearPlayer(virChar_[player1]->m_Pos);
	//virEnemy_[0]->CharaUpdate();



	//ray_->CharaNear(virChar_[player1]->m_Pos, virEnemy_[0]->m_Pos, 50.0);

	//仮キャラ更新
	for (auto chara : charList_)
	{
		chara->CharaUpdate();
		chara->SetAllCharaList(charList_);
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
			//virChar_[player1]->m_Pos = ray_->Slip(virChar_[player1]->m_Dir, vNormal);//滑りベクトルを計算
			chara->SlipMove(ray_->Slip(chara->m_Dir, vNormal));
			//滑りベクトル先の壁とのレイ判定 ２重に判定	
			if (ray_->RayIntersect(chara, stage_->GetMeshWallInfo(), &fDistance, &vNormal) && fDistance <= 0.2)
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
	sprintf(str, "Atk(n-1 | s-2) : %d", virChar_[Player1]->GetAtkState());
	debugText_->Render(str, 0, 10);
	sprintf(str, "AtkCount : %d", virChar_[Player1]->GetAtkCnt());
	debugText_->Render(str, 0, 30);
	if (!enemyList_.empty())
	{
		sprintf(str, "count : %d", enemyList_.size());
		debugText_->Render(str, 0, 70);
	}
	//float dist = pow(enemyList_[0]->m_Pos.x - virChar_[player1]->m_Pos.x, 2) + pow(virEnemy_->m_Pos.z - virChar_[player1]->m_Pos.z, 2);
	//sprintf(str, "dist: %f", dist);
	//debugText_->Render(str, 0, 90);
	/*sprintf(str, "count : %i", ray_->GetHitCnt());
	debugText_->Render(str, 0, 70);*/
	//sprintf(str, "pos x : %f :pos z : %f", virEnemy_->GetTargetPos().x, virEnemy_->GetTargetPos().z);
	//debugText_->Render(str, 0, 70);
	//sprintf(str, "pos x : %f :pos z : %f", virEnemy_->m_Pos.x, virEnemy_->m_Pos.z);
	//debugText_->Render(str, 0, 90);

}