//
//	@file	JobManager.h
//	@brief	�E�Ɩ��̏���
//	@date	2016/11/10
//	@outher	�m�ȍ��c

#pragma once
#include "./../Player/PlayerManager.h"

//	�p�����[�^
struct Parameter
{
	unsigned char name_[30];	//�E�Ɩ�
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//�ʏ�U����
	unsigned int specialAtk_;	//����U����
	unsigned int def_;			//�����
	unsigned int waitTime_;		//�ҋ@����
	float speed_;				//�ړ����x
	float weight_;				//�d��
};

//	�E�ƊǗ��N���X
class JobManager :public PlayerManager
{
public:
	JobManager(Controller controller);
	virtual ~JobManager();
	virtual void CharaUpdate();
};

//	���m�N���X
class SwordMan :public JobManager
{
protected:
	virtual void NormalAttack();
	virtual void SpecialAttack();
public:
	SwordMan(Controller controller);
};

//	�����m�N���X
class Witch :public JobManager
{
protected:	
	virtual void NormalAttack();
	virtual void SpecialAttack();
public:
	Witch(Controller controller);
};

//	���m�N���X
class ShieldMan :public JobManager
{
protected:
	virtual void NormalAttack();
	virtual void SpecialAttack();
public:
	ShieldMan(Controller controller);
};

//	���e�m�N���X
class Bomber :public JobManager
{
private:

protected:
	virtual void NormalAttack();
	virtual void SpecialAttack();
public:
	Bomber(Controller controller);
};