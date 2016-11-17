//
//	@file	CharactorManager.h
//	@brief	キャラクター管理クラス
//	@date	2016/11/09
//	@outher	仁科香苗

#pragma once
#include <vector>
#include "./../Origin.h"
#include "./../Mesh/CD3DXMESH_ANIM.h"

//#include "./../DebugDraw/D3D11_TEXT.h"

enum MIME
{
	player=0,
	queen,
	enemy,
};

class CharactorManager:public CD3DXMESH_ANIM
{
protected:
	MIME mime_;
	float opponentWeight_;	//進行方向にいるキャラの重さ
	bool hitWall_;			//壁にぶつかっているかどうか

	std::vector<CharactorManager*> aroundCharaList_;

	virtual void Move(float speed) = 0;					//移動
	virtual void Attack() = 0;							//攻撃
	virtual void Dead() = 0;							//死亡
	virtual void Motion_Update()=0;						//モーション更新
	void KnockBack(D3DXVECTOR3 atkPos, float distance);	//ノックバック
	void Rotation(D3DXVECTOR3 dirVec);					//キャラの回転
public:
	CharactorManager();
	virtual ~CharactorManager();

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName)=0;		//初期化・読み込み
	virtual void CharaUpdate()=0;								//更新
	void CharaRender(D3DXMATRIX mView,D3DXMATRIX mProj);		//描画
	//void CharaDestroy();										//解放
	void SlipMove(D3DXVECTOR3 slopVec);							//壁滑り用移動
	void StopMove();											//静止用
	void Move_Update();											//移動の更新

	void SetAroundChara(CharactorManager* charactor);	//周辺にいるキャラクターをリストにセット
	void SetOppWeight(float weight);					//進行方向にいるキャラクターの重さセット
	//void SetHitWall(bool wallHitFlg);					//壁にぶつかっているかどうかの更新

	//デバッグ用
	bool GetWallHitFlg()const { return hitWall_; };
};

