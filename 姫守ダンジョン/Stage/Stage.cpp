//
//	@file	Stage.cpp
//	@brief	ステージ関連
//	@date	2016/11/07
//	@outher	仁科香苗
#include "./Stage.h"

//
//	@brief	コンストラクタ
Stage::Stage()
{
	stageMesh_ = new CD3DXMESH_ANIM;
}

//
//	@brief デストラクタ
Stage::~Stage()
{
	SAFE_DELETE(stageMesh_);
}

//
//	@brief						Xファイル読み込み
//	@param (m_hWnd)				ウィンドウハンドル
//	@param (m_pDevice)			デバイス
//	@param (m_pDeviceContext)	デバイスコンテキスト
//	@param (fileName)			Xファイル名
void Stage::Read(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName)
{
	char FileName[80];
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Stage/");
	strcat_s(FileName, sizeof(FileName), fileName);
	if (FAILED(stageMesh_->Init(m_hWnd, m_pDevice, m_pDeviceContext, FileName)))
	{
		return;
	}
}

//
//	@brief			描画
//	@param (mView)	描画用マトリックス
//	@param (mProj)	射影変換用マトリックス
void Stage::Render(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	stageMesh_->Render(mView, mProj, D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1));
}