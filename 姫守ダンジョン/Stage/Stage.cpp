//
//	@file	Stage.cpp
//	@brief	ステージ関連
//	@date	2016/11/07
//	@author	仁科香苗
#include "./Stage.h"

CD3DXMESH* Stage::stage_;

//
//	@brief	コンストラクタ
Stage::Stage()
{
	creator_ = new CharactorCreator;
}

//
//	@brief	デストラクタ
Stage::~Stage()
{
	SAFE_DELETE(stage_);
	delete creator_;
	creator_ = nullptr;
}

//
//	@brief				初期化
//	@param(stageName)	ステージ名
void Stage::Init(char* stageName)
{
	stage_ = creator_->LoadStage(stageName);
}

//
//	@brief	現在いるステージのメッシュ情報取得
CD3DXMESH* Stage::GetMeshInfo()
{
	return stage_;
}

//
//	@brief			描画
void Stage::Render()
{
	stage_->Render(D3DXVECTOR3(0, -0.01, 0), D3DXVECTOR3(0, 0, 0), 1);
}