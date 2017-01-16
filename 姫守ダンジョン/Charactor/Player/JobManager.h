//
//	@file	JobManager.h
//	@brief	職業毎の処理
//	@date	2016/11/10
//	@author	仁科香苗

#pragma once
#include "./../Player/PlayerManager.h"
#include "./../../Read/ParameterRead.h"
#include "./../../Collision.h"
#include "./../../Mesh/CD3DXMESH.h"
#include "./Job/WeaponBall.h"
#include "./../../UI/TD_Graphics.h"

#define UI_SPACE	20		//プレイヤー1と画面端の隙間
#define UI_INTERVAL	480		//UIとUIの間隔(CharaTypeに乗算する)

//	職業管理クラス
class JobManager :public PlayerManager
{
protected:
	TD_Graphics* backUI_;
	TD_Graphics* jobMarkUI_;
	TD_Graphics* hpGageUI_;
	D3DXVECTOR2 backUIPos_;
	D3DXVECTOR2 jobUIPos_;
	D3DXVECTOR2 hpGazePos_;
	//unsigned int timeCount_;	//攻撃時間
	//unsigned int timeAtkEnd_;		//攻撃終了時間
	int attackCount_;			//攻撃ボタンカウント
	Collision* col_;

	void UIRender();
	virtual void WeaponUpdate() {};
public:
	JobManager(CharaType charaType);
	virtual ~JobManager();

	virtual void CharaUpdate();
	//template<class> p;
	//void SetParameter(JobParameter* param);
	//PlayerParameter GetParam()const;

	int GetAtkCnt() { return attackCount_; };

	//デバック用
	PlayerParameter* GetParam()const { return param_; };
};

