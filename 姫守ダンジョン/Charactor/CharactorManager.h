//
//	@file	CharactorManager.h
//	@brief	キャラクター管理クラス
//	@date	2016/11/09
//	@outher	仁科香苗

#pragma once
#include <vector>
#include "./../Origin.h"
#include "./../Mesh/CD3DXSKINMESH.h"
#include "./../Collision.h"

using namespace SKINMESH;

//#include "./../DebugDraw/D3D11_TEXT.h"
enum CharaType
{
	Player1=0,
	Player2,
	Player3,
	Player4,
	Queen,
	Enemy,
};


class CharactorManager:public CD3DXSKINMESH
{
protected:
	CharaType charaType_;
	Collision* collision_;
	int hp_;
	float opponentWeight_;	//進行方向にいるキャラの重さ
	float ownWright_;		//自身の重さ
	bool aliveFlg_;			//生存フラグ
	D3DXVECTOR3 ownPush_;	//自分を押している方向ベクトル

	float knockBackDis_;
	bool knockBackFlg_;
	D3DXVECTOR3 knockBackPos_;

	std::vector<CharactorManager*> aroundCharaList_;	//周辺にいるキャラ
	std::vector<CharactorManager*> allCharaList_;		//全てのキャラ
	virtual void Move(float speed) = 0;					//移動
	virtual void Attack() = 0;							//攻撃
	virtual void Dead() = 0;							//死亡
	virtual void Motion_Update()=0;						//モーション更新
	void KnockBack(D3DXVECTOR3 atkPos, float distance);	//ノックバック
	void Rotation(D3DXVECTOR3 dirVec);					//キャラの回転
	void AroundCharaCheck();
	void MoveCharaHit();
public:
	CharactorManager();
	virtual ~CharactorManager();

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName)=0;		//初期化・読み込み
	virtual void CharaUpdate()=0;								//更新
	virtual void CharaRender(D3DXMATRIX mView,D3DXMATRIX mProj);		//描画
	//void CharaDestroy();										//解放
	void SlipMove(D3DXVECTOR3 slopVec);							//壁滑り用移動
	void StopMove();											//静止用
	void Move_Update();											//移動の更新

	void SetAroundChara(CharactorManager* charactor);	//周辺にいるキャラクターをリストにセット
	void SetAllCharaList(std::vector<CharactorManager*> list);
	void SetOppWeight(float weight);					//進行方向にいるキャラクターの重さセット
	void SetKnockBack(D3DXVECTOR3 pos, float dist);
	bool GetAliveFlg() { return aliveFlg_; };
	CharaType GetCharaType()const;
};

