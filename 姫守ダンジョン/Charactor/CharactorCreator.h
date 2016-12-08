//
//	@file	CharactorCreator.h
//	@brief	キャラクター生成クラス
//	@date	2016/11/14
//	@author	仁科香苗

#pragma once
#include <map>
#include <string>

typedef std::string ObjectType;

//
//	@brief	生成器ベース
template<class Base>
class CreatorBase
{
public:
	virtual ~CreatorBase() {};
	virtual Base* Create() const = 0;
};

//
//	@brief	生成する型と基底クラス指定
template<class Product,class Base>
class Creator :public CreatorBase<Base>
{
public:
	virtual Base* Create() const { return new Product; };
};

//
//	@brief	生成と登録
template<class Base>
class CharactorCreator
{
private:
	typedef std::map<ObjectType, CreatorBase<Base> *> CreatorMap;
	CreatorMap creatorMap_;
public:
	//キャラクターの生成命令
	Base* Create(ObjectType type);

	//生成器を登録
	bool Register(ObjectType, CreatorBase<Base>*creator);
};

//
//	@brief 生成器登録処理
template<class Base>
bool CharactorCreator<Base>::Register(ObjectType, CreatorBase<Base>*creator)
{
	// データがない場合は、コンテナの終端が返ってくる
	CreatorMap::iterator it = creatorMap_.find(type);

	// 既にデータがある場合は生成器を削除する
	if (it != creatorMap_.end())
	{
		delete creator;
		return false;
	}

	creatorMap_[type] = creator;
	return true;
}

//
//	@brief	生成
template<class Base>
Base* Create(ObjectType type)
{
	CreatorMap::iterator it = creatorMap_.find(type);

	// 生成器がなければ失敗
	if (it == creatorMap_.end())
	{
		return nullptr;
	}

	CreatorBase<Base>* creator = (*it).second;
	return creator->Create();
}