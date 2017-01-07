//
//	@file	CharactorCreator.h
//	@brief	キャラクター生成クラス
//	@date	2016/11/14
//	@author	仁科香苗

#pragma once
#include <map>
#include <string>
#include <vector>
#include "./../Mesh/CD3DXMESH.h"
#include "./../Mesh/CD3DXSKINMESH.h"
#include "./../Read/XFileRead.h"

struct CharaModel
{
	char name_[30];
	CD3DXSKINMESH* mesh_;
};

struct StageModel
{
	char name_[30];
	CD3DXMESH* mesh_;
};

class CharactorCreator
{
	static std::vector<CharaModel*> charaModelList_;
	static std::vector<StageModel*> stageModelList_;
public:
	static void LoadModel();
	CD3DXMESH* GetStageModel(char* name);
	CD3DXSKINMESH* GetCharaModel(char* name);
	static void Destroy();

};