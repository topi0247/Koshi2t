//
//	@file	XFileRead.h
//	@brief	Xファイル読み込み
//	@date	2016/11/07
//	@author	仁科香苗

#include "XFileRead.h"

//
//	@brief				XFileクラスコンストラクタ
//	@param (element)	読み込む要素
XFile::XFile(XMLElement* element, const char* type)
{
	//タイプ取得
	memset(type_, 0, sizeof(type_));
	strcpy_s(type_, sizeof(type_), type);

	//ファイル名取得
	memset(fileName_, 0, sizeof(fileName_));
	strcpy_s(fileName_, sizeof(fileName_) - 1, element->Attribute("fileName"));

	//キャラネーム取得
	memset(charName_, 0, sizeof(charName_));
	strcpy_s(charName_, sizeof(charName_) - 1, element->Attribute("charName"));

	if (strcmp(type, "Player") == 0)
	{
		filePath_ = "./Model/XFiles/Player/"+(std::string)fileName_;
	}
	else if (strcmp(type, "Enemy") == 0)
	{
		filePath_ = "./Model/XFiles/Enemy/" + (std::string)fileName_;
	}
	else if (strcmp(type, "Princess") == 0)
	{
		filePath_ = "./Model/XFiles/Princess/" + (std::string)fileName_;
	}
	else
	{
		filePath_ = "./Model/XFiles/Stage/" + (std::string)fileName_;
	}
}

//
//	@brief	XFileReadクラスコンストラクタ
XFileRead::XFileRead()
	:count_(0)
	, xfileList_(0)
{
}

//
//	@brief	XFileReadクラスデストラクタ
XFileRead::~XFileRead()
{
	for (int i = 0; i < count_; i++)
	{
		delete xfileList_[i];
	}
	delete[] xfileList_;
}

//
//	@brief	Xファイルの情報読み込み
void XFileRead::ReadXFilePath()
{
	tinyxml2::XMLDocument xml;
	XMLDeclaration* decl = xml.NewDeclaration();
	xml.InsertEndChild(decl);

	//ファイル読み込み
	xml.LoadFile("./ReadData/XFileName.xml");

	//Xファイルの名前とキャラクターネームの取得
	for (XMLElement* models = xml.FirstChildElement("Models"); models != NULL; models = models->NextSiblingElement("Models"))
	{
		const char* type = models->Attribute("Type");
		for (XMLElement* model = models->FirstChildElement("model"); model != NULL; model = model->NextSiblingElement("model"))
		{
			XFile* temp = new XFile(model, type);
			XFile** newList = new XFile*[count_ + 1];

			if (count_ > 0)
			{
				memcpy(newList, xfileList_, sizeof(XFile**)*count_);
			}
			newList[count_] = temp;
			++count_;
			delete[] xfileList_;
			xfileList_ = newList;
		}
	}
}

//
//	@brief			xファイルのパス情報取得
//	@param (name)	取得するモデル名
XFile* XFileRead::GetXFile(const char* name)
{
	for (int i = 0; i < count_; i++)
	{
		if (strcmp(xfileList_[i]->GetCharName(), name) == 0)
		{
			return xfileList_[i];
		}
	}

	return nullptr;
}

//
//	@brief			ステージモデルの情報取得
std::vector<XFile*> XFileRead::GetStageFile()
{
	std::vector<XFile*> temp;
	for (int i = 0; i < count_; i++)
	{
		if (strcmp(xfileList_[i]->GetType(), "Stage") == 0)
		{
			temp.push_back(xfileList_[i]);
		}
	}
	return temp;
}

std::vector<XFile*> XFileRead::GetModelFile()
{
	std::vector<XFile*> temp;
	for (int i = 0; i < count_; i++)
	{
		if (strcmp(xfileList_[i]->GetType(), "Stage") != 0
			&& strcmp(xfileList_[i]->GetType(), "Spawn") != 0)
		{
			temp.push_back(xfileList_[i]);
		}
	}
	return temp;
}

////
////	@brief	xファイルの読み込み
//void XFileRead::ReadXFile(CD3DXMESH_ANIM* mesh, const char*name)
//{
//	XFile* file = GetXFile(name);
//
//	/*if (FAILED((mesh->Init(Origin::GetInstance().m_hWnd, Origin::GetInstance().m_pDevice, Origin::GetInstance().m_pDeviceContext, fileName, texPath))))
//	{
//		return;
//	}*/
//}