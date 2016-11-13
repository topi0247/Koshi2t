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
	virChar_ = new JobManager * [4];
	virEnemy_ = new EnemyJobManager * [3];
	virEnemy_[0] = new Slim;
	virChar_[player1] = new SwordMan(player1);
	virChar_[player2] = new Witch(player2);
	virChar_[player3] = new ShieldMan(player3);
	virChar_[player4] = new Bomber(player4);
}

//
//	@brief	デストラクタ
Main_Scene::~Main_Scene()
{
	delete stage_;
	stage_ = nullptr;

	delete virEnemy_[0];
	virEnemy_[0] = nullptr;

	for (int i = 0; i < 4; i++)
	{
		delete virChar_[i];
		virChar_[i] = nullptr;
	}
	delete[] virChar_;
	virChar_ = nullptr;
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

	xfile = xfileRead->GetXFile("魔導士");
	virChar_[player2]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());

	xfile = xfileRead->GetXFile("盾士");
	virChar_[player3]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());

	xfile = xfileRead->GetXFile("爆弾士");
	virChar_[player4]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	
	xfile = xfileRead->GetXFile("スライム");
	virEnemy_[0]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
}

//
//	@brief	更新
void Main_Scene::Update()
{
	virEnemy_[0]->CheckNearPlayer(virChar_[player1]->GetOwnPos());
	virEnemy_[0]->CharaUpdate();

	//仮キャラ更新
	for (int i = 0; i < 4; i++)
	{
		virChar_[i]->CharaUpdate();
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

	virEnemy_[0]->CharaRender(mView, mProj);

	//仮キャラ描画
	for (int i = 0; i < 4; i++)
	{
		virChar_[i]->CharaRender(mView, mProj);
	}
}