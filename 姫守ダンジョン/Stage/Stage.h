//
//	@file	Stage.h
//	@brief	ステージ関連
//	@date	2016/11/07
//	@outher	仁科香苗

#pragma once
#include "./../Mesh/CD3DXMESH.h"


class Stage
{
	CD3DXMESH* stageMesh_;
	CD3DXMESH* skyMesh_;
	CD3DXMESH* gate_;
	CD3DXMESH* abyssGround_;
	D3DXVECTOR3 m_Pos;
public:
	Stage();
	~Stage();

	void Read(const char* StageName);		//初期化
	void Render();		//描画

	CD3DXMESH* GetMeshInfo()const { return stageMesh_; };		//メッシュの取得
};