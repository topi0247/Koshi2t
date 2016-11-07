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
}

//
//	@brief	デストラクタ
Main_Scene::~Main_Scene()
{
	delete stage_;
	stage_ = nullptr;
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
}

//
//	@brief	更新
void Main_Scene::Update()
{

}

//
//	@brief			描画
//	@param (mView)	描画用マトリックス
//	@param (mProj)	射影変換用マトリックス
void Main_Scene::Render(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	//ステージの描画
	stage_->Render(mView, mProj);
}