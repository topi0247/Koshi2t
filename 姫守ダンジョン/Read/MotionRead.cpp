#include "MotionRead.h"

Motion** MotionRead::playermMotionList_;
Motion** MotionRead::enemyMotionList_;
unsigned int MotionRead::countP_;
unsigned int MotionRead::countE_;

//
//	@brief	モーションクラスコンストラクタ
Motion::Motion(XMLElement* element)
	:count_(0)
	, motionList_(0)
{
	//モーション使用者名
	memset(name_, 0, sizeof(name_));
	memcpy(name_, element->Attribute("name"), sizeof(name_));

	for (XMLElement* motion = element->FirstChildElement("motion"); motion != NULL; motion = motion->NextSiblingElement("motion"))
	{
		MotionAttr* temp = new MotionAttr;
		MotionAttr** newList = new MotionAttr*[count_ + 1];

		memset(temp->name_, 0, sizeof(temp->name_));
		memcpy(temp->name_, motion->Attribute("name"), sizeof(temp->name_));

		temp->id_ = atoi(motion->Attribute("id"));
		temp->frame_ = atoi(motion->Attribute("frame"));

		if (count_ > 0)
		{
			memcpy(newList, motionList_, sizeof(MotionAttr**)*count_);
		}

		newList[count_] = temp;
		++count_;
		delete[] motionList_;
		motionList_ = newList;
	}
}

//
//	@brief	モーションの取得
const MotionAttr* Motion::GetMotion(char* name)const
{
	for (int i = 0; i < count_; i++)
	{
		if (strcmp(name, motionList_[i]->name_) == 0)
		{
			return motionList_[i];
		}
	}

	return nullptr;
}


//
//	@brief	モーション読み込みクラスのコンストラクタ
MotionRead::MotionRead()
{
}

//
//	@brief	モーション読み込みクラスのデストラクタ
MotionRead::~MotionRead()
{
	if (playermMotionList_ != nullptr)
	{
		for (int i = 0; i < countP_; i++)
		{
			delete playermMotionList_[i];
			playermMotionList_[i] = nullptr;
		}
		delete[] playermMotionList_;
		playermMotionList_ = nullptr;
	}

	if (enemyMotionList_ != nullptr)
	{
		for (int i = 0; i < countE_; i++)
		{
			delete enemyMotionList_[i];
			enemyMotionList_[i] = nullptr;
		}
		delete[] enemyMotionList_;
		enemyMotionList_ = nullptr;
	}
}

//
//	@brief	プレイヤーモーションデータ読み込み
void MotionRead::PlayerMotionRead()
{
	XMLDocument xml;
	XMLDeclaration* decl = xml.NewDeclaration();

	//ファイル読み込み
	xml.LoadFile("./ReadData/Motion.xml");

	//モーション情報の取得
	for (XMLElement* job = xml.FirstChildElement("Job"); job != NULL; job = job->NextSiblingElement("Job"))
	{
		Motion* temp = new Motion(job);
		Motion** newList = new Motion*[countP_ + 1];

		if (countP_ > 0)
		{
			memcpy(newList, playermMotionList_, sizeof(Motion**)*countP_);
		}
		newList[countP_] = temp;
		++countP_;
		delete[] playermMotionList_;
		playermMotionList_ = newList;
	}
}

//
//	@brief	エネミーのモーションデータ読み込み
void MotionRead::EnemyMotionRead()
{
	XMLDocument xml;
	XMLDeclaration* decl = xml.NewDeclaration();

	//ファイル読み込み
	xml.LoadFile("./ReadData/EnemyMotion.xml");

	//モーション情報の取得
	for (XMLElement* job = xml.FirstChildElement("Job"); job != NULL; job = job->NextSiblingElement("Job"))
	{
		Motion* temp = new Motion(job);
		Motion** newList = new Motion*[countE_ + 1];

		if (countE_ > 0)
		{
			memcpy(newList, enemyMotionList_, sizeof(Motion**)*countE_);
		}
		newList[countE_] = temp;
		++countE_;
		delete[] enemyMotionList_;
		enemyMotionList_ = newList;
	}
}

//
//	@brief	モーション使用者取得
Motion* MotionRead::GetMotionUser(const char* name)
{

	for (int i = 0; i < countP_; i++)
	{
		if (strcmp(name, playermMotionList_[i]->GetName()) == 0)
		{
			return playermMotionList_[i];
		}
	}

	for (int i = 0; i < countE_; i++)
	{
		if (strcmp(name, enemyMotionList_[i]->GetName()) == 0)
		{
			return enemyMotionList_[i];
		}
	}
	return nullptr;

}