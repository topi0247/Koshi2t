#pragma once
#include "./../../../Origin.h"
#include "./../../Player/JobManager.h"

//	剣士クラス
class SwordMan :public JobManager
{
private:
	void Normal_Attack_Collision();
	void Special_Attack_Collision();
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	SwordMan(Controller controller);
	virtual void Attack();
	//デバッグ用
	float dist;
	D3DXVECTOR3 nor;
};