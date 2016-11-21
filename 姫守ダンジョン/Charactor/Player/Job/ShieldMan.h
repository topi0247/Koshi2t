#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"


//	èÇémÉNÉâÉX
class ShieldMan :public JobManager
{
private:
	D3DXVECTOR3 spMove_;
	void Normal_Attack_Collision();
	void Special_Attack_Collision();
private:
	virtual void Normal_Attack();
	virtual void Special_Attack();
	virtual void Move_Update();
public:
	ShieldMan(Controller controller);
	virtual void Attack();
};
