//
//	@file	Stage.h
//	@brief	ステージ関連
//	@date	2016/11/07
//	@outher	仁科香苗

#pragma once
#include "./../Mesh/CD3DXMESH.h"

using namespace STATICMESH;
class Stage
{
	CD3DXMESH* stageMesh_;
public:
	Stage();
	~Stage();

	void Read(HWND m_phWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext,const char* fileName);		//初期化
	void Render(D3DXMATRIX mView,D3DXMATRIX mProj);		//描画

	CD3DXMESH* GetMeshInfo()const { return stageMesh_; };		//メッシュの取得
};