//
//	@file	CharactorManager.h
//	@brief	キャラクター管理クラス
//	@date	2016/11/09
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#pragma once
#include <vector>
#include "./../Origin.h"
#include "./../Mesh/CD3DXSKINMESH.h"
#include "./../Collision.h"
#include "./../Read/MotionRead.h"
#include "./../Sound/Sound.h"
#include "./../Read/MotionRead.h"
#include "./../Read/ParameterRead.h"
#include "./../Read/XFileRead.h"
#include "./CharactorCreator.h"

//#include "./../DebugDraw/D3D11_TEXT.h"
enum CharaType
{
	Player1=0,
	Player2,
	Player3,
	Player4,
	PrincessT,
	Enemy,
	Non=100,
};


class CharactorManager//:public CD3DXSKINMESH
{
protected:
	CD3DXSKINMESH* mesh_;
	CharactorCreator* creator_;
	//bool effectFlg_;

	Motion* motion_;			//モーション管理クラス
	unsigned int motionNo_;		//現在のモーション番号
	unsigned int motionCount_;	//モーション用カウント
	unsigned int motionFrame_;	//現在のモーションの総フレーム数
	bool motionChange_;			//モーション変更フラグ
	float motionSpeed_;			//モーションスピード
	float motionPlayPos_;		//モーションの再生位置

	float knockBackDis_;		//ノックバック距離
	float knockBackSpeed_;		//ノックバックスピード
	bool knockBackFlg_;			//ノックバックフラグ
	D3DXVECTOR3 knockBackPos_;	//ノックバック開始座標

	CharaType perpetrator_;		//最後に攻撃してきたキャラクター
	Collision* collision_;		//衝突判定クラス
	unsigned int hp_;			//現在のHP
	bool aliveFlg_;				//生存フラグ

	unsigned int damageCount_;		//ダメージ時点滅描画カウントアップ
	unsigned int damageDrawTime_;	//ダメージ時点滅描画時間
	bool damageFlg_;				//ダメージフラグ

	unsigned int spaceNo_;		//座標による空間番号
	float opponentWeight_;		//進行方向にいるキャラの重さ
	bool moveAbleFlg_;			//移動可能フラグ
	bool wallHitFlg_;			//壁との衝突フラグ
	D3DXVECTOR3 ownPush_;		//自分を押している方向ベクトル


	CharaType charaType_;								//自分のキャラクタータイプ
	std::vector<CharactorManager*> aroundCharaList_;	//周辺にいるキャラ

	virtual void Move(float speed) = 0;					//移動
	virtual void Attack() = 0;							//攻撃
	virtual void Dead() = 0;							//死亡
	virtual void MoveCharaHit();						//移動方向にキャラクターがいるかどうか
	void Rotation(D3DXVECTOR3 dirVec);					//キャラの回転
	void AroundCharaCheck();							//周辺にキャラクターがいるかどうか
	virtual void ChangeMotion(Motion* motion,char* name);		//モーションの変更
	virtual void DamageSound() {};						//ダメージサウンド
	virtual void SetParameter(char* name)=0;
public:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Dir;
	float m_Yaw;
	D3DXVECTOR3 m_Scale;

	CharactorManager();
	virtual ~CharactorManager();
	
	static std::vector<CharactorManager*> allCharaList_;		//全てのキャラ
	virtual void CharaInit(char* name);		//初期化・読み込み
	virtual void CharaUpdate()=0;								//更新
	virtual void Reset()=0;										//リセット
	virtual void CharaRender();									//描画
	virtual void Move_Update();									//移動の更新
	virtual void DamageCalc(unsigned int atk)=0;				//ダメージ計算
	void Destroy();												//解放
	void SetMotionData(Motion* motionData);
	void KnockBack(D3DXVECTOR3 atkPos, float distance,float speed);	//ノックバック

	void SlipMove(D3DXVECTOR3 slopVec);							//壁滑り用移動
	void StopMove();											//静止用
	void SetAroundChara(CharactorManager* charactor);			//周辺にいるキャラクターをリストにセット
	//void SetAllCharaList(std::vector<CharactorManager*> list);	//存在している全てのキャラクターセット
	void SetOppWeight(float weight);							//進行方向にいるキャラクターの重さセット
	void SetKnockBack(D3DXVECTOR3 pos, float dist,float speed,CharaType charatype);	//ノックバック情報セット
	void SetKnockBackFlg(bool flg) { knockBackFlg_ = flg; };	//ノックバックフラグセット
	void SetWallHitflg(bool flg) { wallHitFlg_ = flg; };		//壁との衝突フラグセット
	int GetSpaceNo();											//空間番号取得
	bool GetAliveFlg() { return aliveFlg_; };					//生存フラグ取得
	bool GetKnockBackFlg() { return knockBackFlg_; };			//ノックバックフラグ取得
	bool GetDamageFlg() { return damageFlg_; };					//ダメージフラグ取得
	bool GetWallHitFlg() { return wallHitFlg_; };				//壁との衝突フラグ取得
	CharaType GetCharaType()const;								//キャラクタータイプ取得

	//デバッグ用
	int GetAroundC() { return aroundCharaList_.size(); };		//自身の周辺にいるキャラクターの数取得
	unsigned int GetHP()const { return hp_; };					//自身の体力取得
	unsigned int GetMotionNo()const { return motionNo_; };		//自身のモーション番号取得
	float GetMotionSpeed()const { return motionSpeed_; };		//自身のモーションスピード取得
	unsigned int GetMotionCount()const { return motionCount_; };//モーションカウント取得
};

