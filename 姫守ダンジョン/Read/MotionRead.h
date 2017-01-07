#pragma once
#include "./tinyxml2.h"

using namespace tinyxml2;

//
//	@brief	モーションの属性
struct MotionAttr
{
	char name_[30];		//モーション名
	unsigned int id_;	//モーション番号
	unsigned int frame_;	//フレーム数
};

//
//	@brief	モーションデータ
class Motion
{
private:
	char name_[30];				//モーション使用者名
	MotionAttr** motionList_;	//モーション属性リスト
	unsigned int count_;		//モーション数
public:
	Motion(XMLElement* elemnt);
	const char* GetName()const { return name_; };
	const MotionAttr* GetMotion(char* name)const;
	
};

//
//	@brief	モーションリスト読み込みクラス
class MotionRead
{
private:
	static Motion** playermMotionList_;	//プレイヤーモーションリスト
	static Motion** enemyMotionList_;		//エネミーモーションリスト

	static unsigned int countP_;
	static unsigned int countE_;
public:
	MotionRead();
	~MotionRead();

	static void PlayerMotionRead();
	static void EnemyMotionRead();
	Motion* GetMotionUser(const char* name);
};