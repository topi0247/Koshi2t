//
//	@file	ParameterRead.h
//	@brief	パラメータ読み込み
//	@date	2016/11/14
//	@outher	仁科香苗

#include "ParameterRead.h"

using namespace std;

//
//	@brief	JobParameterコンストラクタ
JobParameter::JobParameter(string str)
	:hp_(0)
	, normalAtk_(0)
	, specialAtk_(0)
	, def_(0)
	, chargeTime_(0)
	, specialAttackTime_(0)
	, moveSpeed_(0)
	, specialMoveSpeed_(0)
	, weight_(0)
	, attackReach_(0)
	, scale_(0)
	, attackRange_(0)
{
	//職業名の取得
	string temp = str;
	size_t comma = temp.find(',');
	string pull = temp.substr(0, comma);
	name_ = new char[comma + 1];
	memcpy(name_, pull.c_str(), comma + 1);
	temp = temp.substr(comma + 1);

	//HP取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	hp_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//通常攻撃取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	normalAtk_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//特殊攻撃取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	specialAtk_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//特殊攻撃時間
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	specialAttackTime_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//チャージタイム取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	chargeTime_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//守備力取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	def_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//移動スピード取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	moveSpeed_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//特殊移動スピード取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	specialMoveSpeed_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//重さ取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	weight_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//攻撃リーチ取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	attackReach_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//攻撃範囲取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	attackRange_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//スケール取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	scale_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);
}

//=====================================================================//

//
//	@brief	姫パラメータ読み込み
PrincessParameter::PrincessParameter(string str)
	:moveSpeed_(0)
	, weight_(0)
{
	//職業名の取得
	string temp = str;
	size_t comma = temp.find(',');
	string pull = temp.substr(0, comma + 1);

	//移動スピード取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	moveSpeed_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//重さ取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	weight_ = atof(pull.c_str());
}

//=====================================================================//
//
//	@brief	EnemyParameterコンストラクタ
EnemyParameter::EnemyParameter(string str)
{
	//職業名の取得
	string temp = str;
	size_t comma = temp.find(',');
	string pull = temp.substr(0, comma + 1);
	name_ = new char[comma + 1];
	memcpy(name_, pull.c_str(), comma + 1);
	temp = temp.substr(comma + 1);

	//HP取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	hp_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//通常攻撃取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	normalAtk_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//守備力取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	def_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//移動スピード取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	moveSpeed_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//重さ取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	weight_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//攻撃リーチ取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	attackReach_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//スケール取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	scale_ = atof(pull.c_str());
}

//=======================================================================//

//
//	@brief	ParameterReadコンストラクタ	
ParameterRead::ParameterRead()
	:jobParamList_(0)
	, enemyParamList_(0)
	,princessParam_(0)
	, jobCount_(0)
	, enemyCount_(0)
{
}

//
//	@brief	ParameterReadデストラクタ	
ParameterRead::~ParameterRead()
{
	if (princessParam_ != nullptr)
	{
		delete princessParam_;
		princessParam_ = nullptr;
	}

	if (jobParamList_ != nullptr)
	{
		for (int i = 0; i < jobCount_; i++)
		{
			delete jobParamList_[i];
			jobParamList_[i] = nullptr;
		}
	}

	if (enemyParamList_ != nullptr)
	{
		for (int j = 0; j < enemyCount_; j++)
		{
			delete enemyParamList_[j];
			enemyParamList_[j] = nullptr;
		}
	}
}

//
//	@brief				職業パラメータ読み込み
//	@param (filePath)	csvファイルパス
void ParameterRead::SetJobParameter(const char* filePath)
{
	//ファイルの読み込み
	ifstream ifs(filePath);
	if (!ifs)
	{
		return;
	}

	//一行目はパラメータ名なので飛ばす
	string str;
	getline(ifs, str);

	//データの読み込み
	while (getline(ifs, str))
	{
		JobParameter* temp = new JobParameter(str);
		JobParameter** newList = new JobParameter*[jobCount_ + 1];

		if (jobCount_ > 0)
		{
			memcpy(newList, jobParamList_, sizeof(JobParameter**)*jobCount_);
		}

		newList[jobCount_] = temp;
		++jobCount_;
		delete[] jobParamList_;
		jobParamList_ = newList;
	}

	//ファイルを閉じる
	ifs.close();
}

//
//	@brief				姫パラメータ読み込み
//	@param (filePath)	csvファイルパス
void ParameterRead::SetPriceccParameter(const char* filePath)
{
	//ファイルの読み込み
	ifstream ifs(filePath);
	if (!ifs)
	{
		return;
	}

	//一行目はパラメータ名なので飛ばす
	string str;
	getline(ifs, str);

	//データの読み込み
	getline(ifs, str);
	princessParam_ = new PrincessParameter(str);

	//ファイルを閉じる
	ifs.close();
}

//
//	@brief				敵パラメータ読み込み
//	@param (filePath)	csvファイルパス
void ParameterRead::SetEnemyParameter(const char* filePath)
{
	//ファイルの読み込み
	ifstream ifs(filePath);
	if (!ifs)
	{
		return;
	}

	//一行目はパラメータ名なので飛ばす
	string str;
	getline(ifs, str);

	//データの読み込み
	while (getline(ifs, str))
	{
		EnemyParameter* temp = new EnemyParameter(str);
		EnemyParameter** newList = new EnemyParameter*[jobCount_ + 1];

		if (jobCount_ > 0)
		{
			memcpy(newList, jobParamList_, sizeof(EnemyParameter**)*jobCount_);
		}

		newList[enemyCount_] = temp;
		++jobCount_;
		delete[] jobParamList_;
		enemyParamList_ = newList;
	}

	//ファイルを閉じる
	ifs.close();
}

//
//	@brief	職業数の読み込み
int ParameterRead::GetJobCount()const
{
	return jobCount_;
}

//
//	@brief	エネミー数の読み込み
int ParameterRead::GetEnemyCount()const
{
	return enemyCount_;
}

//
//	@brief			職業パラメータ取得
//	@param (name)	職業名
JobParameter* ParameterRead::GetJobParamList(const char* name)const
{
	for (int i = 0; i < jobCount_; i++)
	{
		if (strcmp(name, jobParamList_[i]->GetName()) == 0)
		{
			return jobParamList_[i];
		}
	}

	return nullptr;
}

//
//	@brief			敵パラメータ取得
//	@param (name)	敵の名前
EnemyParameter* ParameterRead::GetEnemyParamList(const char* name)const
{
	for (int i = 0; i < enemyCount_; i++)
	{
		if (strcmp(name, enemyParamList_[i]->GetName()) == 0)
		{
			return enemyParamList_[i];
		}
	}
	return nullptr;
}