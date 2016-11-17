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
	virChar_[player1] = new SwordMan(player1);
	virChar_[player2] = new Witch(player2);
	virChar_[player3] = new ShieldMan(player3);
	virChar_[player4] = new Bomber(player4);

	for (int i = 0; i < 4; i++)
	{
		charList_.push_back(virChar_[i]);
	}

	ray_ = new Collision;
	virEnemy_ = new EnemyJobManager *[3];
	virEnemy_[0] = new Slim;

	charList_.push_back(virEnemy_[0]);
}

//
//	@brief	デストラクタ
Main_Scene::~Main_Scene()
{
	delete stage_;
	stage_ = nullptr;

	delete ray_;
	ray_ = nullptr;

	delete virEnemy_[0];
	virEnemy_[0] = nullptr;

	for (int i = 0; i < 4; i++)
	{
		delete virChar_[i];
		virChar_[i] = nullptr;
	}
	delete[] virChar_;
	virChar_ = nullptr;

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
	XFile* xfile = xfileRead->GetXFile("ステージ");
	stage_->Read(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());

	//仮キャラファイル読み込み
	xfile = xfileRead->GetXFile("剣士");
	virChar_[player1]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[player1]->m_vPos = D3DXVECTOR3(26, 0, 11);

	xfile = xfileRead->GetXFile("魔導士");
	virChar_[player2]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[player2]->m_vPos = D3DXVECTOR3(26, 0, -11);

	xfile = xfileRead->GetXFile("盾士");
	virChar_[player3]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[player3]->m_vPos = D3DXVECTOR3(-26, 0, 11);

	xfile = xfileRead->GetXFile("爆弾士");
	virChar_[player4]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[player4]->m_vPos = D3DXVECTOR3(-26, 0, -11);

	xfile = xfileRead->GetXFile("スライム");
	virEnemy_[0]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
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

	for (int i = 0; i < 3; i++)
	{
		virEnemy_[0]->SetTargetChar(virChar_[i],virChar_[player4]);
	}
	//virEnemy_[0]->CharaUpdate();

	/*ray_->CharaNear(virChar_[player1]->m_vPos, virEnemy_[0]->m_vPos, 50.0);*/

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
	float fDistance = 0;
	D3DXVECTOR3 vNormal;
	//壁との衝突判定

	//bool wallFlg = false;
	for (auto chara : charList_)
	{
		if (ray_->RayIntersect(chara, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.3)
		{
			//当たり状態なので、滑らせる
			//virChar_[player1]->m_vPos = ray_->Slip(virChar_[player1]->m_Dir, vNormal);//滑りベクトルを計算
			chara->SlipMove(ray_->Slip(chara->m_Dir, vNormal));
			//滑りベクトル先の壁とのレイ判定 ２重に判定	
			if (ray_->RayIntersect(chara, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.2)
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
	//virChar_[player1]->SetHitWall(wallFlg);

	//キャラクター同士の衝突判定
	}

//
//	@brief			描画
//	@param (mView)	描画用マトリックス
//	@param (mProj)	射影変換用マトリックス
void Main_Scene::Render(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	//ステージの描画
	stage_->Render(mView, mProj);

	virEnemy_[0]->CharaRender(mView, mProj);

	//仮キャラ描画
	for (int i = 0; i < 4; i++)
	{
		virChar_[i]->CharaRender(mView, mProj);
	}

	//デバッグ描画
	char str[256];
	sprintf(str, "Atk(n-1 | s-2) : %d", virChar_[player1]->GetAtkState());
	debugText_->Render(str, 0, 10);
	sprintf(str, "AtkCount : %d", virChar_[player1]->GetAtkCnt());
	debugText_->Render(str, 0, 30);
	sprintf(str, "axis : %f", virChar_[player1]->m_AxisZ.z);
	debugText_->Render(str, 0, 50);
	sprintf(str, "count : %i", ray_->GetHitCnt());
	debugText_->Render(str, 0, 70);
	sprintf(str, "pos x : %f :pos z : %f", virEnemy_[0]->GetTargetPos().x, virEnemy_[0]->GetTargetPos().z );
	debugText_->Render(str, 0, 90);

}