//
//	@file	XFileRead.h
//	@brief	Xファイル読み込み
//	@date	2016/11/07
//	@outher	仁科香苗

#pragma once
#include "./../Origin.h"
#include "./../Mesh/CD3DXMesh_Anim.h"
#include "./tinyxml2.h"

using namespace tinyxml2;

//
//	@brief	読み込むXファイルの情報クラス
class XFile
{
	char type_[30];
	char fileName_[30];
	char charName_[30];
public:
	XFile(XMLElement* element,const char* type);

	const char* GetType()const { return type_; };
	const char* GetFileName()const { return fileName_; };
	const char* GetCharName()const { return charName_; };
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

	XFile* GetXFile(const char*);	//Xファイルのパス情報取得
	void ReadXFilePath();			//Xファイルのパス情報読み込み
	//void ReadXFile(CD3DXMESH_ANIM* mesh,const char* name);			//Xファイルの読み込み
	int GetCount()const { return count_; };
};

