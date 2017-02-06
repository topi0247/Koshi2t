//
//	@file	Stage.h
//	@brief	ステージ関連
//	@date	2016/11/07
//	@author	仁科香苗

#pragma once
#include <vector>
#include "./../Mesh/CD3DXMESH.h"
#include "./../Camera.h"
#include "./../Read/XFileRead.h"
#include "./../Charactor/CharactorCreator.h"

class Stage
{
	CharactorCreator* creator_;		//モデル読み込み
	static CD3DXMESH* stage_;		//ステージメッシュ
public:
	Stage();
	~Stage();

	void Init(char* stageName);		//初期化
	void Render();					//描画
	static CD3DXMESH* GetMeshInfo();//メッシュの取得
};