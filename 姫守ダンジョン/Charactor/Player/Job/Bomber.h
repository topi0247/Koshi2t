#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"

//	”š’emƒNƒ‰ƒX
class Bomber :public JobManager
{
private:
	bool bombFlg_;	//”š’e‚ª”­“®’†‚©‚Ç‚¤‚©
	bool invincibleFlg_;	//–³“G’†‚©‚Ç‚¤‚©
	int bombCount_;
	float bombScale_;
	//WeaponBall** bomb_;
	std::vector<WeaponBall*> bomb_;
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Bomber(CharaType charaType);
	virtual ~Bomber();
	virtual void Attack();
	virtual void Move_Update();
	virtual void DamageCalc(unsigned int atk);					//ƒ_ƒ[ƒWŒvZ
	virtual void CharaRender(D3DXMATRIX mView, D3DXMATRIX mProj);
};