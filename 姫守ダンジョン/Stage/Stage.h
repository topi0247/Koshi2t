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

//struct StageMesh
//{
//	CD3DXMESH* stageMesh_;
//	D3DXVECTOR3 pos_;
//	char stageName[10];
//	bool drawFlg_;
//	int stageNo_;
//};

class Stage
{
	CharactorCreator* creator_;
	//std::vector<StageMesh*> stage_;
	static CD3DXMESH* stage_;
	//CD3DXMESH* skyMesh_;
	CD3DXMESH* gate_;
	CD3DXMESH* abyssGround_;
	//D3DXVECTOR3 m_Pos;
public:
	Stage();
	~Stage();

	//void Read(std::vector<XFile*> xfile,char* name);	//初期化
	void Init(char* stageName);
	void Render();				//描画
	//void Destroy();
	CD3DXMESH* GetMeshInfo()const;		//メッシュの取得
};