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
#include "./../Read/MotionRead.h"

//#include "./../DebugDraw/D3D11_TEXT.h"
enum CharaType
{
	Player1=0,
	Player2,
	Player3,
	Player4,
	PrincessT,
	Enemy,
};


class CharactorManager:public CD3DXSKINMESH
{
protected:
	Motion* motion_;

	CharaType charaType_;
	Collision* collision_;
	unsigned int hp_;
	unsigned int motionNo_;
	unsigned int motionCount_;
	float motionSpeed_;
	float opponentWeight_;	//進行方向にいるキャラの重さ
	float ownWright_;		//自身の重さ
	bool aliveFlg_;			//生存フラグ
	bool moveAbleFlg_;		//移動可能フラグ
	D3DXVECTOR3 ownPush_;	//自分を押している方向ベクトル

	float knockBackDis_;
	float knockBackSpeed_;
	bool knockBackFlg_;
	D3DXVECTOR3 knockBackPos_;

	std::vector<CharactorManager*> aroundCharaList_;	//周辺にいるキャラ
	std::vector<CharactorManager*> allCharaList_;		//全てのキャラ
	virtual void Move(float speed) = 0;					//移動
	virtual void Attack() = 0;							//攻撃
	virtual void Dead() = 0;							//死亡
	void Rotation(D3DXVECTOR3 dirVec);					//キャラの回転
	void AroundCharaCheck();
	void MoveCharaHit();
public:
	CharactorManager();
	virtual ~CharactorManager();

	virtual const char* CharaInit(const char* fileName)=0;		//初期化・読み込み
	virtual void CharaUpdate()=0;								//更新
	virtual void CharaRender();									//描画
	virtual void Move_Update();									//移動の更新
	virtual void DamageCalc(unsigned int atk) = 0;				//ダメージ計算
	void SetMotionData(Motion* motionData);
	void KnockBack(D3DXVECTOR3 atkPos, float distance,float speed);	//ノックバック

	void SlipMove(D3DXVECTOR3 slopVec);							//壁滑り用移動
	void StopMove();											//静止用
	void SetAroundChara(CharactorManager* charactor);			//周辺にいるキャラクターをリストにセット
	void SetAllCharaList(std::vector<CharactorManager*> list);
	void SetOppWeight(float weight);							//進行方向にいるキャラクターの重さセット
	void SetKnockBack(D3DXVECTOR3 pos, float dist,float speed);
	bool GetAliveFlg() { return aliveFlg_; };
	CharaType GetCharaType()const;

	unsigned int GetHP()const { return hp_; };
};

