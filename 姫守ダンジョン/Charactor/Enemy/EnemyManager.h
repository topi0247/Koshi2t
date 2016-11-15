//
//	@file	EnemyManager.h
//	@brief	“GŠÇ—ƒNƒ‰ƒX
//	@date	2016/11/13
//	@outher	‹g‰z‘å‹R

#pragma once
#include "./../CharactorManager.h"
#include "./../../DebugDraw/D3D11_TEXT.h"

class EnemyManager : public CharactorManager
{
private:
	D3DXVECTOR3 targetPos_;
	enum TargetObject
	{
		princess = 0,
		player,
	};
	TargetObject targetObj;
protected:

	virtual void NormalAttack() = 0;	//’ÊíUŒ‚
	virtual void Attack();				//UŒ‚
	virtual void Move(float speed);		//ˆÚ“®ˆ—
	virtual void Dead();				//€–S
	virtual void Motion_Update() {};	//ƒ‚[ƒVƒ‡ƒ“XV
	void Spawn();						//“GƒXƒ|[ƒ“

public:
	EnemyManager() { m_vPos.z = 10; };
	virtual ~EnemyManager() {};
	
	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);		//‰Šú‰»E“Ç‚İ‚İ

	void CheckNearPlayer(D3DXVECTOR3 position);	//‹ß‚­‚É‚¢‚é‚©”»•Ê
	D3DXVECTOR3 GetOwnPos()const { return m_vPos; };
};

