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
	//stageMesh_ = new CD3DXMESH;
	//m_Pos = D3DXVECTOR3(0, -0.2, 0);
	//skyMesh_ = new CD3DXMESH;
	//gate_ = new CD3DXMESH;
	//abyssGround_ = new CD3DXMESH;
	//stage_ = new CD3DXMESH;
	//skyMesh_ = new CD3DXMESH;
	//gate_ = new CD3DXMESH;
	//abyssGround_ = new CD3DXMESH;
	creator_ = new CharactorCreator;
}

//
//	@brief	デストラクタ
Stage::~Stage()
{
	//SAFE_DELETE(stage_);
	////SAFE_DELETE(skyMesh_);
	//SAFE_DELETE(gate_);
	//SAFE_DELETE(abyssGround_);
	delete creator_;
	creator_ = nullptr;
}


//
//	@brief	Xファイル読み込み
//void Stage::Read(std::vector<XFile*> xfile, char* name)
//{

	////int stageCount = 0;
	////int stageSizeZ = 32;
	//for (auto x : xfile)
	//{

	//	char FileNameF[80];
	//	memset(FileNameF, 0, sizeof(FileNameF));
	//	strcpy_s(FileNameF, sizeof(FileNameF), "./Model/XFiles/Stage/");
	//	strcat_s(FileNameF, sizeof(FileNameF), x->GetFileName());

	//	if (strcmp(x->GetCharName(), name) == 0)
	//	{
	//		if (FAILED(stage_->LoadXMesh(FileNameF)))
	//		{
	//			return;
	//		}
	//	}
	//	else if (strstr(x->GetCharName(), "門"))
	//	{
	//		if (FAILED(gate_->LoadXMesh(FileNameF)))
	//		{
	//			return;
	//		}
	//	}
	//	else if (strstr(x->GetCharName(), "地面"))
	//	{
	//		if (FAILED(abyssGround_->LoadXMesh(FileNameF)))
	//		{
	//			return;
	//		}
	//	}
	//}
//}

void Stage::Init(char* stageName)
{
	//CharactorCreator* creator=new CharactorCreator;
	gate_ = creator_->LoadStage("門");
	abyssGround_ = creator_->LoadStage("地面");
	stage_ = creator_->LoadStage(stageName);

	//delete creator;
	//creator = nullptr;
}

//
//	@brief	現在いるステージのメッシュ情報取得
CD3DXMESH* Stage::GetMeshInfo()const
{
	/*for (auto s : stage_)
	{
		if (s->stageNo_ == stageType)
		{
			return s->stageMesh_;
		}
	}*/
	return stage_;
}

//
//	@brief			描画
//	@param (mView)	描画用マトリックス
//	@param (mProj)	射影変換用マトリックス
void Stage::Render()
{
	stage_->Render(D3DXVECTOR3(0, -0.01, 0), D3DXVECTOR3(0, 0, 0), 1);
	//abyssGround_->Render(D3DXVECTOR3(0, -1, 0), D3DXVECTOR3(0, 0, 0), 1);
	gate_->Render(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1);

	/*for (auto s : stage_)
	{
		if (s->drawFlg_)
		{
			s->stageMesh_->Render(s->pos_, D3DXVECTOR3(0, 0, 0), 1);
		}
	}*/

	////static float scale = 1;
	////デバック用
	////scale += -((GetKeyState(VK_F1) & 0x80)*0.0001) + ((GetKeyState(VK_F2) & 0x80)*0.0001);
	////
	//D3DXVECTOR3 stopPos(Camera::GetGazePoint().x, 0, Camera::GetGazePoint().z);

	//stageMesh_->Render(m_Pos,D3DXVECTOR3(0,0,0),1);

	//skyMesh_->Render(stopPos, D3DXVECTOR3(D3DXToRadian(90), 0, 0), 3);

	////gate_->Render(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1);
	//stopPos.y = -2;
	//abyssGround_->Render(stopPos, D3DXVECTOR3(0, 0, 0), 1);
}