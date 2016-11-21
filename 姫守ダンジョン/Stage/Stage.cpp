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
	stageMeshFloor_ = new CD3DXMESH;
	stageMeshWall_ = new CD3DXMESH;
}

//
//	@brief デストラクタ
Stage::~Stage()
{
	SAFE_DELETE(stageMeshFloor_);
	SAFE_DELETE(stageMeshWall_);
}

//
//	@brief						Xファイル読み込み
//	@param (m_hWnd)				ウィンドウハンドル
//	@param (m_pDevice)			デバイス
//	@param (m_pDeviceContext)	デバイスコンテキスト
//	@param (FloorName)			床のXファイル名
//	@param (WallName)			壁のXファイル名
void Stage::Read(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* FloorName, const char* WallName)
{
	char FileNameF[80];
	memset(FileNameF, 0, sizeof(FileNameF));
	strcpy_s(FileNameF, sizeof(FileNameF), "./Model/XFiles/Stage/");
	strcat_s(FileNameF, sizeof(FileNameF), FloorName);
	if (FAILED(stageMeshFloor_->Init(m_hWnd, m_pDevice, m_pDeviceContext, FileNameF)))
	{
		return;
	}
	
	char FileNameW[80];
	memset(FileNameW, 0, sizeof(FileNameW));
	strcpy_s(FileNameW, sizeof(FileNameW), "./Model/XFiles/Stage/");
	strcat_s(FileNameW, sizeof(FileNameW), WallName);
	if (FAILED(stageMeshWall_->Init(m_hWnd, m_pDevice, m_pDeviceContext, FileNameW)))
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
	stageMeshFloor_->Render(mView, mProj, D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1));
	stageMeshWall_->Render(mView, mProj, D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1));
}