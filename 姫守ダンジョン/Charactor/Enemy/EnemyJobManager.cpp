//
//	@file	EnemyJobManager.cpp
//	@brief	敵ごとの処理
//	@date	2016/11/13
//	@author	吉越大騎
//	@author	仁科香苗


#include "EnemyJobManager.h"

EnemyJobManager::EnemyJobManager()
{
}

EnemyJobManager::~EnemyJobManager()
{
}

//
//	@brief	リセット
void EnemyJobManager::Reset()
{
	hp_ = param_->hp_;
	motionChange_ = true;
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	aroundCharaList_.clear();
	allCharaList_.clear();
}

void EnemyJobManager::CharaUpdate()
{
	//m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);

	//空間番号の更新
	spaceNo_ = collision_->SetSpaceNo(m_Pos,2);
	
	//進行方向にキャラクターがいるか
	MoveCharaHit();

	//移動処理
	float speed = param_->moveSpeed_;
	Move(speed);

	//ターゲットキャラの更新
	Target_Update();

	//攻撃処理
	Attack();

	//攻撃モーションからの遷移
	if (motionNo_ == motion_->GetMotion("attack")->id_)
	{
		if (++motionCount_ > motionFrame_)
		{
			ChangeMotion(motion_, "walk");
		}
	}

	//if (state_ == walk)
	//{
	//	//motionNo_ = motion_->GetMotion("walk")->id_;
	//}
	//else if (state_ == attack)
	//{
	//	//motionNo_ = motion_->GetMotion("attack")->id_;
	//	if (++motionCount_ > motionFrame_)
	//	{
	//		state_ == walk;
	//		motionCount_ = 0;
	//	}
	//}
}


//=======スライム=======//
//Slim::Slim()
//{
//}

void Slim::NormalAttack()
{
	float dist = 1;
	float speed = 0.1;
	targetChar_->DamageCalc(param_->atk_);
	//targetChar_->KnockBack(m_Pos,dist,speed);
	targetChar_->SetKnockBack(m_Pos, dist, speed, charaType_);
	ChangeMotion(motion_, "attack");
}

//=======ゴブリン========//
void Goblin::NormalAttack()
{
	float dist = param_->attackReach_;
	float speed = 0.1;
	targetChar_->DamageCalc(param_->atk_);
	targetChar_->SetKnockBack(m_Pos, dist, speed, charaType_);
	ChangeMotion(motion_, "attack");
}

//=======スケルトン======//


//
//	@brief	リセット
void Skeleton::Reset()
{
	hp_ = param_->hp_;
	motionChange_ = true;
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	aroundCharaList_.clear();
	allCharaList_.clear();
	atkList_.clear();
}

void Skeleton::NormalAttack()
{
	float dist = 1;
	float speed = 0.01;
	WeaponBall* atkBall = new WeaponBall();
	D3DXVECTOR3 vec(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);
	atkBall->SetDir(vec);
	//atkBall->SetDamageList(allCharaList_, charaType_,1);
	//atkBall->SetKnockBack(dist, param_->attackReach_, speed, charaType_,!charaType_);
	atkBall->SetAttack(param_->atk_);
	atkList_.push_back(atkBall);
	ChangeMotion(motion_, "attack");
}


void Skeleton::CharaRender()
{
	//mesh_->m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);
	bool drawFlg = true;
	if (damageFlg_)
	{
		if (++damageCount_ % 5 == 0)
		{
			drawFlg = false;
		}
	}

	if (drawFlg)
	{
		float scale = 0.2f;
		mesh_->Render(m_Pos, m_Yaw, D3DXVECTOR3(scale, scale, scale));
	}

	if (!atkList_.empty())
	{
		for (auto a : atkList_)
		{
			a->Render(a->GetPosition());
		}
	}
}