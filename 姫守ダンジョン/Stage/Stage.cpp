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
	stageMesh_ = new CD3DXMESH;
	m_Pos = D3DXVECTOR3(0, 0, 0);
}

//
//	@brief デストラクタ
Stage::~Stage()
{
	SAFE_DELETE(stageMesh_);
}

//
//	@brief						Xファイル読み込み
void Stage::Read(const char* StageName)
{
	char FileNameF[80];
	memset(FileNameF, 0, sizeof(FileNameF));
	strcpy_s(FileNameF, sizeof(FileNameF), "./Model/XFiles/Stage/");
	strcat_s(FileNameF, sizeof(FileNameF), StageName);

	if (FAILED(stageMesh_->LoadXMesh(FileNameF)))
	{
		return;
	}
	
}

//
//	@brief			描画
//	@param (mView)	描画用マトリックス
//	@param (mProj)	射影変換用マトリックス
void Stage::Render()
{
	stageMesh_->Render(m_Pos,0,1);
}