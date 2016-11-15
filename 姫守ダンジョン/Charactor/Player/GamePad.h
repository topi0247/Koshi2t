//
//	@file	GamePad.h
//	@brief	�Q�[���p�b�h�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�s��

#pragma once
#include <windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib")

//�Q�[���p�b�h�Ɋւ��鏈�����܂Ƃ߂����O���
namespace GamePad
{
	//�Q�[���p�b�h �e������ ���͔���p
	enum InputName
	{
		////�f�W�^��
		DirectionPad_Up,	//�����p�b�h�F��
		DirectionPad_Down,	//�����p�b�h�F��
		DirectionPad_Left,	//�����p�b�h�F��
		DirectionPad_Right,	//�����p�b�h�F�E
		A,					//A�{�^��
		B,					//B�{�^��
		X,					//X�{�^��
		Y,					//Y�{�^��
		LB,					//L�{�^��
		RB,					//R�{�^��
		START,				//START�{�^��
		BACK,				//BACK�{�^��
		LeftStick_Push,		//���X�e�B�b�N�F��������
		RightStick_Push,	//�E�X�e�B�b�N�F��������

		////�A�i���O
		LT,					//L�g���K�[
		RT,					//R�g���K�[
		LeftStick_Up,		//���X�e�B�b�N�F��
		LeftStick_Down,		//���X�e�B�b�N�F��
		LeftStick_Left,		//���X�e�B�b�N�F��
		LeftStick_Right,	//���X�e�B�b�N�F�E
		RightStick_Up,		//�E�X�e�B�b�N�F��
		RightStick_Down,	//�E�X�e�B�b�N�F��
		RightStick_Left,	//�E�X�e�B�b�N�F��
		RightStick_Right,	//�E�X�e�B�b�N�F�E

		////���̑�
		//�v�f��
		InputName_NUM
	};

	//�Q�[���p�b�h �e������ �A�i���O���l�擾�p
	enum AnalogName
	{
		//�g���K�[
		AnalogName_LT,
		AnalogName_RT,

		//�X�e�B�b�N
		AnalogName_LeftStick_X,		//���X�e�B�b�N�FX��
		AnalogName_LeftStick_Y,		//���X�e�B�b�N�FY��
		AnalogName_RightStick_X,	//�E�X�e�B�b�N�FX��
		AnalogName_RightStick_Y,	//�E�X�e�B�b�N�FY��

		//�v�f��
		AnalogName_NUM,
	};


	//------//
	// �֐� //
	//------//

	//�X�V
	void update();	

	//����p
	bool checkInput(int,InputName);		//���͂��Ă��true��Ԃ�
	bool checkOnInput(int, InputName);	//���͂��n�߂��u�Ԃ�true��Ԃ�
	bool checkOffInput(int, InputName);	//���͂��I������u�Ԃ�true��Ԃ�

	//���l�擾�p
	float getAnalogValue(int, AnalogName);	//�A�i���O�̓��͒l��Ԃ��i�l�͐��K���j
};
