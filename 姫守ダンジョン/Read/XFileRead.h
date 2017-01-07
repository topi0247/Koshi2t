//
//	@file	XFileRead.h
//	@brief	Xファイル読み込み
//	@date	2016/11/07
//	@author	仁科香苗
//	@author 吉越大騎(エフェクト・UI)

#pragma once
#include <vector>
#include <string>
#include "./../Origin.h"
#include "./../Mesh/CD3DXSKINMESH.h"
#include "./tinyxml2.h"

using namespace tinyxml2;

//
//	@brief	読み込むXファイルの情報クラス
class XFile
{
	char type_[30];
	char fileName_[30];
	char charName_[30];
	std::string filePath_;
public:
	XFile(XMLElement* element,const char* type);

	const char* GetType()const { return type_; };
	const char* GetFileName()const { return fileName_; };
	const char* GetCharName()const { return charName_; };
	char* GetFilePath()const 
	{ 
		int len = filePath_.length();
		char* path = new char[len+1];
		memcpy(path, filePath_.c_str(), len + 1);
		return path; 
	};
};

//
//	@brief	Xファイル読み込みクラス
class XFileRead
{
	XFile** xfileList_;				//Xファイル管理
	int count_;						//読み込むXファイル数

public:
	XFileRead();
	~XFileRead();

	XFile* GetXFile(const char*);	//Xファイルの情報取得
	std::vector<XFile*> GetStageFile();
	std::vector<XFile*> GetModelFile();
	void ReadXFilePath();			//Xファイルのパス情報読み込み
	//void ReadXFile(CD3DXMESH_ANIM* mesh,const char* name);			//Xファイルの読み込み
	int GetCount()const { return count_; };
};