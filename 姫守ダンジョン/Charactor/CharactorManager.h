//
//	@file	CharactorManager.h
//	@brief	キャラクター管理クラス
//	@date	2016/11/09
//	@outher	仁科香苗

#pragma once
#include "./../Origin.h"
#include "./../Mesh/CD3DXMESH_ANIM.h"

class CharactorManager:public CD3DXMESH_ANIM
{
protected:
	virtual const char* Read(const char* fileName)=0;	//読み込み
	virtual void Move(float speed) = 0;			//移動
	virtual void Attack() = 0;					//攻撃
	virtual void Dead() = 0;					//死亡
	virtual void Motion_Update()=0;				//モーション更新
	void KnockBack(D3DXVECTOR3 ownPos, D3DXVECTOR3 opponentPos, float distance);	//ノックバック
	void Rotation(D3DXVECTOR3 dirVec);			//キャラの回転
	
public:
	CharactorManager();
	virtual ~CharactorManager() {};

	void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);		//初期化・読み込み
	virtual void CharaUpdate()=0;								//更新
	void CharaRender(D3DXMATRIX mView,D3DXMATRIX mProj);		//描画
	//void CharaDestroy();										//解放
};

