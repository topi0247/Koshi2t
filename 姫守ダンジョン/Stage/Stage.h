//
//	@file	Stage.h
//	@brief	ステージ関連
//	@date	2016/11/07
//	@outher	仁科香苗

#pragma once
#include "./../Mesh/CD3DXMESH_ANIM.h"

class Stage
{
	CD3DXMESH_ANIM* stageMesh_;
public:
	Stage();
	~Stage();

	void Read(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext,const char* fileName);		//初期化
	void Render(D3DXMATRIX mView,D3DXMATRIX mProj);		//描画

	CD3DXMESH_ANIM* GetMeshInfo()const { return stageMesh_; };		//メッシュの取得
};