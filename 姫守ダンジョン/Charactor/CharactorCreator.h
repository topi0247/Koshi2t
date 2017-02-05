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
#include "./../Read/MotionRead.h"
#include "./../Read/ParameterRead.h"

//struct CharaModel
//{
//	char name_[30];
//	CD3DXSKINMESH* mesh_;
//};
//
//struct StageModel
//{
//	char name_[30];
//	CD3DXMESH* mesh_;
//};

class CharactorCreator
{
	//static std::vector<CharaModel*> charaModelList_;
	//static std::vector<StageModel*> stageModelList_;
	static XFileRead* xfileRead;
public:
	static char player1_[10];
	static char player2_[10];
	static char player3_[10];
	static char player4_[10];

	//static void LoadModel();

	static void LoadData();
	static void LoadXFileName();
	static void Destroy();
	CD3DXSKINMESH* LoadChara(char* name);
	CD3DXMESH* LoadStage(char* name);


	//CD3DXMESH* GetStageModel(char* name);
	//CD3DXSKINMESH* GetCharaModel(char* name);
	//static void Destroy();

};