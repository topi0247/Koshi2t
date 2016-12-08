//
//	@file	GamePad.cpp
//	@brief	ゲームパッド管理クラス
//	@date	2016/11/09
//	@author	不明

#include "GamePad.h"


namespace GamePad
{
	//入力閾値
	const int Threshold[4] = {
		XINPUT_GAMEPAD_TRIGGER_THRESHOLD,	//Trigger
		32500,								//Stick最大値
		32500 / 2,							//Stick中間値
		//XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE,	//LeftStick
		//XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE	//RightStick
	};

	//ゲームパッド状態を保存する構造体
	struct GamePad
	{
		bool input[InputName_NUM];				//各部が入力されているか trueなら使用中
		SHORT AnalogValue[AnalogName_NUM];		//アナログ入力値
	};


	//------------------//
	// pribate 変数作成 //
	//------------------//

	//ゲームパッド作成
	GamePad now[4], old[4];		//新しいもの、古いもの

	XINPUT_STATE state[4];	//情報取得用
	DWORD dwResult[4];		//関数結果判定用


	//-----------------//
	// public 関数定義 //
	//-----------------//

	//更新
	void update()
	{
		for (int i = 0; i < 4; i++)
		{
			old[i] = now[i];

			ZeroMemory(&state[i], sizeof(XINPUT_STATE));	//初期化
			dwResult[i] = XInputGetState(i, &state[i]);		//情報取得

			//// 各入力状態の取得
			//情報取得できていたら実行
			if (dwResult[i] == ERROR_SUCCESS)
			{
				////デジタル
				now[i].input[InputName::DirectionPad_Up] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
				now[i].input[InputName::DirectionPad_Down] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
				now[i].input[InputName::DirectionPad_Left] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
				now[i].input[InputName::DirectionPad_Right] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
				now[i].input[InputName::A] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_A;
				now[i].input[InputName::B] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_B;
				now[i].input[InputName::X] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_X;
				now[i].input[InputName::Y] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_Y;
				now[i].input[InputName::LB] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
				now[i].input[InputName::RB] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
				now[i].input[InputName::START] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_START;
				now[i].input[InputName::BACK] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
				now[i].input[InputName::LeftStick_Push] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
				now[i].input[InputName::RightStick_Push] = state[i].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;

				////アナログ
				now[i].input[InputName::LT] = (state[i].Gamepad.bLeftTrigger > Threshold[0]) ? true : false;
				now[i].input[InputName::RT] = (state[i].Gamepad.bRightTrigger > Threshold[0]) ? true : false;
				now[i].input[InputName::LeftStick_Up] = (state[i].Gamepad.sThumbLY > Threshold[2]) ? true : false;
				now[i].input[InputName::LeftStick_Down] = (state[i].Gamepad.sThumbLY < -Threshold[2]) ? true : false;
				now[i].input[InputName::LeftStick_Left] = (state[i].Gamepad.sThumbLX > Threshold[2]) ? true : false;
				now[i].input[InputName::LeftStick_Right] = (state[i].Gamepad.sThumbLX < -Threshold[2]) ? true : false;
				now[i].input[InputName::RightStick_Up] = (state[i].Gamepad.sThumbRY > Threshold[2]) ? true : false;
				now[i].input[InputName::RightStick_Down] = (state[i].Gamepad.sThumbRY < -Threshold[2]) ? true : false;
				now[i].input[InputName::RightStick_Left] = (state[i].Gamepad.sThumbRX > Threshold[2]) ? true : false;
				now[i].input[InputName::RightStick_Right] = (state[i].Gamepad.sThumbRX < -Threshold[2]) ? true : false;

				//数値
				now[i].AnalogValue[AnalogName::AnalogName_LT] = state[i].Gamepad.bLeftTrigger;			//左トリガー
				now[i].AnalogValue[AnalogName::AnalogName_RT] = state[i].Gamepad.bRightTrigger;			//右トリガー
				now[i].AnalogValue[AnalogName::AnalogName_LeftStick_Y] = state[i].Gamepad.sThumbLY;		//左スティックY軸
				now[i].AnalogValue[AnalogName::AnalogName_LeftStick_X] = state[i].Gamepad.sThumbLX;		//左スティックX軸
				now[i].AnalogValue[AnalogName::AnalogName_RightStick_Y] = state[i].Gamepad.sThumbRY;	//右スティックY軸
				now[i].AnalogValue[AnalogName::AnalogName_RightStick_X] = state[i].Gamepad.sThumbRX;	//右スティックX軸
			}
		}
	}



	//入力してればtrueを返す
	bool checkInput(int index,InputName Name)
	{
		//NUMだったら要素数overなので除外する
		if (Name == InputName_NUM)
		{
			return false;
		}

		return now[index].input[Name];	//そのまま返す
	}
	//入力し始めた瞬間にtrueを返す
	bool checkOnInput(int index, InputName Name)
	{
		//NUMだったら要素数overなので除外する
		if (Name == InputName_NUM)
		{
			return false;
		}

		//false false	>> false&false	>> false
		//false true	>> ture&false	>> false
		//true false	>> true&true	>> true
		//true true		>> false&true	>> false
		return (now[index].input[Name] ^ now[index].input[Name]) & (now[index].input[Name]);	//true false の場合のみtrueが返る
	}
	//入力し終わった瞬間にtrueを返す
	bool checkOffInput(int index, InputName Name)
	{
		//NUMだったら要素数overなので除外する
		if (Name == InputName_NUM)
		{
			return false;
		}

		//false false	>> false&true	>> false
		//false true	>> ture&true	>> true
		//true false	>> true&false	>> false
		//true true		>> false&false	>> false
		return (now[index].input[Name] ^ now[index].input[Name]) & (!now[index].input[Name]);	//false true の場合のみtrueが返る
	}

	//数値取得
	float getAnalogValue(int index, AnalogName name)
	{
		switch (name)
		{
			//トリガー
		case AnalogName::AnalogName_LT:
		case AnalogName::AnalogName_RT:
			return (float)now[index].AnalogValue[name] / (float)Threshold[0];
			break;

			//スティック
		case AnalogName::AnalogName_LeftStick_X:
		case AnalogName::AnalogName_LeftStick_Y:
		case AnalogName::AnalogName_RightStick_X:
		case AnalogName::AnalogName_RightStick_Y:
			return (float)now[index].AnalogValue[name] / (float)Threshold[1];
			break;

			//範囲外
		case AnalogName::AnalogName_NUM:
		default:
			return 0;
			break;
		}
	}
}
