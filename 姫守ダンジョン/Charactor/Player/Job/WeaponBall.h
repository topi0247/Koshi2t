//
//	@file	WeaponBall.h
//	@brief	飛び道具クラス
//	@date	2016/11/21
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#pragma once
#include "./../../../Origin.h"
#include "./../../CharactorManager.h"
#include "./../../../Effekseer/Effect.h"
#include "./../../../Stage/Stage.h"

//
//	@brief	飛び道具
class WeaponBall
{
private:
	std::string hitSoundName_;
	unsigned int spaceNo_;
	Collision* col_;
	//CD3DXMESH* weaponBall_;
	//CharactorCreator* creator_;
	CharaType damageChara_;
	CharaType user_;
	std::vector<CharactorManager*> damageList_;				//被弾する可能性のあるキャラクターリスト
	std::vector<CharactorManager*> beforeDamageCharaList_;
	bool delFlg_;
	bool hitDelFlg_;
	bool effectflg_;
	bool w_ball;
	bool hitDel_;
	int delCount_;
	unsigned int atk_;
	float dist_;
	float kDist_;
	float kSpeed_;
	float scale_;
	D3DXVECTOR3 startPos_;
	D3DXVECTOR3 dir_;
	D3DXVECTOR3 pos_;
	void Hit();
public:
	WeaponBall();
	~WeaponBall();
	void Init(char* name);
	void SetDir(D3DXVECTOR3 dir);
	void SetScale(float scale);
	void SetStartPos(D3DXVECTOR3 pos);
	//void SetHitDelFlg();
	void Move_Weapon(float speed);
	void Time_Del_Weapon(int frame);
	//void SetDamageList(std::vector<CharactorManager*> chara,CharaType cType,int no);
	//void SetDamageChara(CharactorManager* chara);
	void SetAttack(unsigned int atk);
	void SetKnockBack(float dist, float kDist,float kSpeed,CharaType userChara,CharaType damageChara);
	void SetHitSound(std::string name);
	void SetHitDelFlg(bool flg);
	void Render(D3DXVECTOR3 pos);
	bool GetDelFlg()const;
	float GetScale()const;
	D3DXVECTOR3 GetPosition()const;
};