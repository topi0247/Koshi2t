//
//	@file	ParameterRead.h
//	@brief	パラメータ読み込み
//	@date	2016/11/14
//	@outher	仁科香苗

#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>

//
//	@brief	プレイヤー職業パラメータ
class JobParameter
{
	char* name_;				//職業名
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//通常攻撃力
	unsigned int specialAtk_;	//特殊攻撃力
	unsigned int def_;			//守備力
	float specialAttackTime_;	//待機時間
	float chargeTime_;			//チャージタイム
	float moveSpeed_;			//移動速度
	float specialMoveSpeed_;	//特殊移動速度
	float weight_;				//重さ
	float attackReach_;			//攻撃リーチ
	float attackRange_;			//攻撃範囲
	float scale_;				//スケール
public:
	JobParameter(std::string str);
	const char* GetName()const { return name_; };				//名前取得
	unsigned int GetHP()const { return hp_; };					//HP取得
	unsigned int GetNormalAtk()const { return normalAtk_; };	//通常攻撃力取得
	unsigned int GetSpAtk()const { return specialAtk_; };		//特殊攻撃力取得
	unsigned int GetDefense()const { return def_; };			//守備力取得
	float GetChargeTime()const { return chargeTime_; };			//チャージタイム取得
	float GetWaitTime()const { return specialAttackTime_; };	//待機時間取得
	float GetMoveSpeed()const { return moveSpeed_; };			//移動速度取得
	float GetWeight()const { return weight_; };					//重さ取得
	float GetAttackReach_()const { return attackReach_; };		//攻撃リーチ取得
	float GetScale()const { return scale_; };					//スケール取得
};

//
//	@brief	姫パラメータ
class PrincessParameter
{
	float moveSpeed_;	//移動速度
	float weight_;		//重さ
public:
	PrincessParameter(std::string str);
	float GetMoveSpeed()const { return moveSpeed_; };	//移動速度取得
	float GetWeight()const { return weight_; };			//重さ取得
};

//
//	@brief	敵パラメータ
class EnemyParameter
{
	char* name_;				//敵の名前
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//通常攻撃
	unsigned int def_;			//守備力
	float moveSpeed_;			//移動スピード
	float weight_;				//重さ
	float attackReach_;			//攻撃リーチ
	float scale_;				//スケール
public:
	EnemyParameter(std::string str);
	const char* GetName()const { return name_; };				//名前取得
	unsigned int GetHP()const { return hp_; };					//HP取得
	unsigned int GetNormalAtk()const { return normalAtk_; };	//通常攻撃力取得
	float GetMoveSpeed()const { return moveSpeed_; };			//移動スピード取得
	float GetWeight()const { return weight_; };					//重さ取得
	float GetAttackReach()const {return attackReach_; };		//攻撃リーチ取得
	float GetScale()const { return scale_; };					//スケール取得
};

//
//	@brief	パラメータ読み込みクラス
//	@note	呼び出しも行う
class ParameterRead
{
	JobParameter** jobParamList_;		//職業パラメータ格納
	PrincessParameter* princessParam_;	//姫パラメータ格納
	EnemyParameter** enemyParamList_;	//敵パラメータ格納

	int jobCount_;		//職業数
	int enemyCount_;	//敵の種類数
public:
	ParameterRead();
	~ParameterRead();
	void SetJobParameter(const char* filePath);		//職業パラメータ読み込み
	void SetPriceccParameter(const char* filePath);	//姫パラメータ読み込み
	void SetEnemyParameter(const char* filePath);	//敵パラメータ読み込み

	JobParameter* GetJobParamList(const char* name)const;					//職業パラメータ呼び出し
	PrincessParameter* GetPrincessParam()const { return princessParam_; };	//姫パラメータ呼び出し
	EnemyParameter* GetEnemyParamList(const char* name)const;				//敵パラメータ呼び出し

};
