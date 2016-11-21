//
//	@file	Stage.h
//	@brief	ステージ関連
//	@date	2016/11/07
//	@outher	仁科香苗

#pragma once
#include "./../Mesh/CD3DXMESH_ANIM.h"

class Stage
{
	CD3DXMESH_ANIM* stageMeshFloor_;
	CD3DXMESH_ANIM* stageMeshWall_;
public:
	Stage();
	~Stage();

	void Read(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext,const char* FloorName, const char* WallName);		//初期化
	void Render(D3DXMATRIX mView,D3DXMATRIX mProj);		//描画

	CD3DXMESH_ANIM* GetMeshFloorInfo()const { return stageMeshFloor_; };		//メッシュの取得
	CD3DXMESH_ANIM* GetMeshWallInfo()const { return stageMeshWall_; };		//メッシュの取得
};