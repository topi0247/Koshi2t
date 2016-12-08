//
//	@file	Stage.cpp
//	@brief	ステージ関連
//	@date	2016/11/07
//	@author	仁科香苗
#include "./Stage.h"

//
//	@brief	コンストラクタ
Stage::Stage()
{
	stageMesh_ = new CD3DXMESH;
	m_Pos = D3DXVECTOR3(0, -0.2, 0);
	skyMesh_ = new CD3DXMESH;
	gate_ = new CD3DXMESH;
	abyssGround_ = new CD3DXMESH;


}

//
//	@brief デストラクタ
Stage::~Stage()
{
	SAFE_DELETE(stageMesh_);
	SAFE_DELETE(skyMesh_);
	SAFE_DELETE(gate_);
	SAFE_DELETE(abyssGround_);
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

	if (FAILED(skyMesh_->LoadXMesh("./Model/XFiles/Stage/sky.x")))
	{
		return;
	}
	
	if (FAILED(gate_->LoadXMesh("./Model/XFiles/Stage/gate.x")))
	{
		return;
	}

	if (FAILED(abyssGround_->LoadXMesh("./Model/XFiles/Stage/mapbase.x")))
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
	//static float scale = 1;
	//デバック用
	//scale += -((GetKeyState(VK_F1) & 0x80)*0.0001) + ((GetKeyState(VK_F2) & 0x80)*0.0001);
	//
	stageMesh_->Render(m_Pos,D3DXVECTOR3(0,0,0),1);

	skyMesh_->Render(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(D3DXToRadian(90), 0, 0), 3);

	gate_->Render(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1);

	abyssGround_->Render(D3DXVECTOR3(0, -2, 0), D3DXVECTOR3(0, 0, 0), 1);
}