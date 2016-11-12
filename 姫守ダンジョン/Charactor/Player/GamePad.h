//
//	@file	GamePad.h
//	@brief	ゲームパッド管理クラス
//	@date	2016/11/09
//	@outher	不明

#pragma once
#include <windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib")

//ゲームパッドに関する処理をまとめた名前空間
namespace GamePad
{
	//ゲームパッド 各部名称 入力判定用
	enum InputName
	{
		////デジタル
		DirectionPad_Up,	//方向パッド：上
		DirectionPad_Down,	//方向パッド：下
		DirectionPad_Left,	//方向パッド：左
		DirectionPad_Right,	//方向パッド：右
		A,					//Aボタン
		B,					//Bボタン
		X,					//Xボタン
		Y,					//Yボタン
		LB,					//Lボタン
		RB,					//Rボタン
		START,				//STARTボタン
		BACK,				//BACKボタン
		LeftStick_Push,		//左スティック：押し込み
		RightStick_Push,	//右スティック：押し込み

		////アナログ
		LT,					//Lトリガー
		RT,					//Rトリガー
		LeftStick_Up,		//左スティック：上
		LeftStick_Down,		//左スティック：下
		LeftStick_Left,		//左スティック：左
		LeftStick_Right,	//左スティック：右
		RightStick_Up,		//右スティック：上
		RightStick_Down,	//右スティック：下
		RightStick_Left,	//右スティック：左
		RightStick_Right,	//右スティック：右

		////その他
		//要素数
		InputName_NUM
	};

	//ゲームパッド 各部名称 アナログ数値取得用
	enum AnalogName
	{
		//トリガー
		AnalogName_LT,
		AnalogName_RT,

		//スティック
		AnalogName_LeftStick_X,		//左スティック：X軸
		AnalogName_LeftStick_Y,		//左スティック：Y軸
		AnalogName_RightStick_X,	//右スティック：X軸
		AnalogName_RightStick_Y,	//右スティック：Y軸

		//要素数
		AnalogName_NUM,
	};


	//------//
	// 関数 //
	//------//

	//更新
	void update();	

	//判定用
	bool checkInput(int,InputName);		//入力してればtrueを返す
	bool checkOnInput(int, InputName);	//入力し始めた瞬間にtrueを返す
	bool checkOffInput(int, InputName);	//入力し終わった瞬間にtrueを返す

	//数値取得用
	float getAnalogValue(int, AnalogName);	//アナログの入力値を返す（値は正規化）
};
