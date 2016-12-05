#include "./SpawnGateRead.h"


//
//	@brief	スポーンゲートクラスのコンストラクタ
SpawnGate::SpawnGate(XMLElement* element)
	:spawnGateList_(0)
	,count_(0)
{
	memset(stageName_, 0, sizeof(stageName_));
	strcpy_s(stageName_, sizeof(stageName_), element->Attribute("Type"));

	for (XMLElement* spawn = element->FirstChildElement("spawn"); spawn != NULL; spawn = spawn->NextSiblingElement("spawn"))
	{
		SpawnGateAttr* temp = new SpawnGateAttr;

		temp->id_ = atoi(spawn->Attribute("id"));
		float x = atof(spawn->Attribute("x"));
		float y = atof(spawn->Attribute("y"));
		float z = atof(spawn->Attribute("z"));
		temp->pos_ = D3DXVECTOR3(x, y, z);
		memset(temp->enemyName_, 0, sizeof(temp->enemyName_));
		strcpy_s(temp->enemyName_, sizeof(temp->enemyName_), spawn->Attribute("enemyName"));
		temp->amount_ = atoi(spawn->Attribute("amount"));
		temp->interval_ = atoi(spawn->Attribute("interval"));
		temp->spawnRange_ = atoi (spawn->Attribute("range"));

		SpawnGateAttr** newList = new SpawnGateAttr*[count_ + 1];

		if (count_ > 0)
		{
			memcpy(newList, spawnGateList_, sizeof(SpawnGateAttr**)*count_);
		}

		newList[count_] = temp;
		++count_;
		delete[] spawnGateList_;
		spawnGateList_ = newList;
	}
}

//
//	@brief	スポーンゲートクラスのデストラクタ
SpawnGate::~SpawnGate()
{
	/*for (int i = 0; i < count_; i++)
	{
		delete spawnGateList_[i];
		spawnGateList_[i] = nullptr;
	}
	delete[] spawnGateList_;
	spawnGateList_ = nullptr;*/
}

//
//	@brief	1ステージ上に存在するスポーンゲート情報の取得
std::vector<SpawnGateAttr*> SpawnGate::GetStageAllSpawnGate()
{
	std::vector<SpawnGateAttr*> temp;
	for (int i = 0;i < count_; i++)
	{
		temp.push_back(spawnGateList_[i]);
	}

	return temp;
}


//
//	@brief	スポーンゲート読み込みクラスコンストラクタ
SpawnGateRead::SpawnGateRead()
	:spawnGateList_(0)
	,count_(0)
{
}

//
//	@brief	スポーンゲート読み込みクラスデストラクタ
SpawnGateRead::~SpawnGateRead()
{
	for (int i = 0; i < count_; i++)
	{
		delete spawnGateList_[i];
		spawnGateList_[i] = nullptr;
	}
	delete[] spawnGateList_;
	spawnGateList_ = nullptr;
}

//
//	@brief	スポーンゲートの読み込み
void SpawnGateRead::SpawnGate_Read()
{
	tinyxml2::XMLDocument xml;
	XMLDeclaration* decl = xml.NewDeclaration();

	//ファイル読み込み
	xml.LoadFile("./ReadData/Spawn.xml");

	//スポーンゲート情報の取得
	for (XMLElement* stage = xml.FirstChildElement("Stage"); stage != NULL; stage = stage->NextSiblingElement("Stage"))
	{
		SpawnGate* temp = new SpawnGate(stage);
		SpawnGate** newList = new SpawnGate*[count_ + 1];

		if (count_ > 0)
		{
			memcpy(newList, spawnGateList_, sizeof(SpawnGate**)*count_);
		}
		newList[count_] = temp;
		++count_;
		delete[] spawnGateList_;
		spawnGateList_ = newList;
	}
}

//
//	@brief	1ステージのスポーンゲート情報の取得
SpawnGate* SpawnGateRead::GetSpawnGate(const char* stageName)
{
	for (int i = 0; i < count_; i++)
	{
		if (strcmp(stageName, spawnGateList_[i]->GetStageName()) == 0)
		{
			return spawnGateList_[i];
		}
	}

	return nullptr;
}