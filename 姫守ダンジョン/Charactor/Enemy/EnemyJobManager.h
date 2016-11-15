//
//	@file	JobManager.h
//	@brief	�G���Ƃ̏���
//	@date	2016/11/13
//	@outher	�g�z��R

#pragma once
#include "./../Enemy/EnemyManager.h"

//	�p�����[�^
struct EnemyParameter
{
	unsigned char name_[30];	//�G�̖�
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//�ʏ�U����
	unsigned int def_;			//�����
	unsigned int waitTime_;		//�ҋ@����
	float speed_;				//�ړ����x
	float weight_;				//�d��
};

//	�E�ƊǗ��N���X
class EnemyJobManager :public EnemyManager
{
public:
	EnemyJobManager();
	virtual ~EnemyJobManager();
	virtual void CharaUpdate();
};

//	�X���C���N���X
class Slim :public EnemyJobManager
{
protected:
	virtual void NormalAttack();
public:
	//Slim() {};
	virtual ~Slim() {};
};