//
//	@file	ParameterRead.h
//	@brief	パラメータ読み込み
//	@date	2016/11/14
//	@author	仁科香苗

#include "ParameterRead.h"

using namespace std;

//
//	@brief	JobParameterコンストラクタ
JobParameter::JobParameter(string str)
	:hp_(0)
	, normalAtk_(0)
	, specialAtk_(0)
	, def_(0)
	, chainWeapon_(0)
	, spChainWeapon_(0)
	, invisibleTime_(0)
	, weaponDelTime_(0)
	, chargeTime_(0)
	, moveSpeed_(0)
	, specialMoveSpeed_(0)
	, attackReach_(0)
	, attackRange_(0)
	, knockbackSpeed_(0)
	, knockbackDist_(0)
	, weaponScale_(0)
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

	//特殊攻撃範囲
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	specialAtkRange_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//ノックバック速度
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	knockbackSpeed_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//ノックバック距離
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	knockbackDist_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//無敵時間
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	invisibleTime_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//通常時飛び道具連続発動回数
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	chainWeapon_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//特殊時飛び道具連続発動回数
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	spChainWeapon_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//飛び道具スケール
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	weaponScale_= atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//飛び道具消滅時間
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	weaponDelTime_ = atoi(pull.c_str());
	//temp = temp.substr(comma + 1);
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
	//名前の取得
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

	//攻撃取得
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	atk_ = atoi(pull.c_str());
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

JobParameter** ParameterRead::jobParamList_;
PrincessParameter* ParameterRead::princessParam_;
EnemyParameter** ParameterRead::enemyParamList_;
int ParameterRead::jobCount_;
int ParameterRead::enemyCount_;

//
//	@brief	ParameterReadコンストラクタ	
ParameterRead::ParameterRead()
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
	delete[] jobParamList_;
	jobParamList_ = nullptr;

	if (enemyParamList_ != nullptr)
	{
		for (int j = 0; j < enemyCount_; j++)
		{
			delete enemyParamList_[j];
			enemyParamList_[j] = nullptr;
		}
	}
	delete[] enemyParamList_;
	enemyParamList_ = nullptr;
}

//
//	@brief				職業パラメータ読み込み
//	@param (filePath)	csvファイルパス
void ParameterRead::SetJobParameter(/*const char* filePath*/)
{
	//ファイルの読み込み
	ifstream ifs("./ReadData/JobParameterData.csv");
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
void ParameterRead::SetPricessParameter(/*const char* filePath*/)
{
	////ファイルの読み込み
	//ifstream ifs("");
	//if (!ifs)
	//{
	//	return;
	//}

	////一行目はパラメータ名なので飛ばす
	//string str;
	//getline(ifs, str);

	////データの読み込み
	//getline(ifs, str);
	//princessParam_ = new PrincessParameter(str);

	////ファイルを閉じる
	//ifs.close();
}

//
//	@brief				敵パラメータ読み込み
//	@param (filePath)	csvファイルパス
void ParameterRead::SetEnemyParameter(/*const char* filePath*/)
{
	//ファイルの読み込み
	ifstream ifs("./ReadData/EnemyParameterData.csv");
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
		EnemyParameter** newList = new EnemyParameter*[enemyCount_ + 1];

		if (enemyCount_ > 0)
		{
			memcpy(newList, enemyParamList_, sizeof(EnemyParameter**)*enemyCount_);
		}

		newList[enemyCount_] = temp;
		++enemyCount_;
		delete[] enemyParamList_;
		enemyParamList_ = newList;
	}

	//ファイルを閉じる
	ifs.close();
}

//
//	@brief	職業数の取得
int ParameterRead::GetJobCount()const
{
	return jobCount_;
}

//
//	@brief	エネミー数の取得
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