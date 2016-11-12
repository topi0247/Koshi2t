//
//	@file	GamePad.cpp
//	@brief	�Q�[���p�b�h�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�s��

#include "GamePad.h"


namespace GamePad
{
	//����臒l
	const int Threshold[4] = {
		XINPUT_GAMEPAD_TRIGGER_THRESHOLD,	//Trigger
		32500,								//Stick�ő�l
		32500 / 2,							//Stick���Ԓl
		//XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE,	//LeftStick
		//XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE	//RightStick
	};

	//�Q�[���p�b�h��Ԃ�ۑ�����\����
	struct GamePad
	{
		bool input[InputName_NUM];				//�e�������͂���Ă��邩 true�Ȃ�g�p��
		SHORT AnalogValue[AnalogName_NUM];		//�A�i���O���͒l
	};


	//------------------//
	// pribate �ϐ��쐬 //
	//------------------//

	//�Q�[���p�b�h�쐬
	GamePad now[4], old[4];		//�V�������́A�Â�����

	XINPUT_STATE state[4];	//���擾�p
	DWORD dwResult[4];		//�֐����ʔ���p


	//-----------------//
	// public �֐���` //
	//-----------------//

	//�X�V
	void update()
	{
		for (int i = 0; i < 4; i++)
		{
			old[i] = now[i];

			ZeroMemory(&state[i], sizeof(XINPUT_STATE));	//������
			dwResult[i] = XInputGetState(i, &state[i]);		//���擾

			//// �e���͏�Ԃ̎擾
			//���擾�ł��Ă�������s
			if (dwResult[i] == ERROR_SUCCESS)
			{
				////�f�W�^��
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

				////�A�i���O
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

				//���l
				now[i].AnalogValue[AnalogName::AnalogName_LT] = state[i].Gamepad.bLeftTrigger;			//���g���K�[
				now[i].AnalogValue[AnalogName::AnalogName_RT] = state[i].Gamepad.bRightTrigger;			//�E�g���K�[
				now[i].AnalogValue[AnalogName::AnalogName_LeftStick_Y] = state[i].Gamepad.sThumbLY;		//���X�e�B�b�NY��
				now[i].AnalogValue[AnalogName::AnalogName_LeftStick_X] = state[i].Gamepad.sThumbLX;		//���X�e�B�b�NX��
				now[i].AnalogValue[AnalogName::AnalogName_RightStick_Y] = state[i].Gamepad.sThumbRY;	//�E�X�e�B�b�NY��
				now[i].AnalogValue[AnalogName::AnalogName_RightStick_X] = state[i].Gamepad.sThumbRX;	//�E�X�e�B�b�NX��
			}
		}
	}



	//���͂��Ă��true��Ԃ�
	bool checkInput(int index,InputName Name)
	{
		//NUM��������v�f��over�Ȃ̂ŏ��O����
		if (Name == InputName_NUM)
		{
			return false;
		}

		return now[index].input[Name];	//���̂܂ܕԂ�
	}
	//���͂��n�߂��u�Ԃ�true��Ԃ�
	bool checkOnInput(int index, InputName Name)
	{
		//NUM��������v�f��over�Ȃ̂ŏ��O����
		if (Name == InputName_NUM)
		{
			return false;
		}

		//false false	>> false&false	>> false
		//false true	>> ture&false	>> false
		//true false	>> true&true	>> true
		//true true		>> false&true	>> false
		return (now[index].input[Name] ^ now[index].input[Name]) & (now[index].input[Name]);	//true false �̏ꍇ�̂�true���Ԃ�
	}
	//���͂��I������u�Ԃ�true��Ԃ�
	bool checkOffInput(int index, InputName Name)
	{
		//NUM��������v�f��over�Ȃ̂ŏ��O����
		if (Name == InputName_NUM)
		{
			return false;
		}

		//false false	>> false&true	>> false
		//false true	>> ture&true	>> true
		//true false	>> true&false	>> false
		//true true		>> false&false	>> false
		return (now[index].input[Name] ^ now[index].input[Name]) & (!now[index].input[Name]);	//false true �̏ꍇ�̂�true���Ԃ�
	}

	//���l�擾
	float getAnalogValue(int index, AnalogName name)
	{
		switch (name)
		{
			//�g���K�[
		case AnalogName::AnalogName_LT:
		case AnalogName::AnalogName_RT:
			return (float)now[index].AnalogValue[name] / (float)Threshold[0];
			break;

			//�X�e�B�b�N
		case AnalogName::AnalogName_LeftStick_X:
		case AnalogName::AnalogName_LeftStick_Y:
		case AnalogName::AnalogName_RightStick_X:
		case AnalogName::AnalogName_RightStick_Y:
			return (float)now[index].AnalogValue[name] / (float)Threshold[1];
			break;

			//�͈͊O
		case AnalogName::AnalogName_NUM:
		default:
			return 0;
			break;
		}
	}
}
