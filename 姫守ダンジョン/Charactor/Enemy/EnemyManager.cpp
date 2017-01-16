//
//	@file	EnemyManager.cpp
//	@brief	エネミー管理クラス
//	@date	2016/11/13
//	@author　吉越大騎
//	@author	仁科香苗

#include "EnemyManager.h"

std::vector<D3DXVECTOR3> EnemyManager::busStop_;
std::vector<int> EnemyManager::busStopSpaceNo_;

EnemyManager::EnemyManager()
{
	charaType_ = Enemy;
	m_Pos = { 0,0,0 };
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	//opponentWeight_ = 1;
	//targetPos_ = D3DXVECTOR3(0, 0, 0);
	collision_ = new Collision;
	param_ = new EnemyParam;
}

EnemyManager::~EnemyManager()
{
	delete collision_;
	collision_ = nullptr;
	//delete motion_;
	//motion_ = nullptr;
}


//
//	@brief	パラメータセット
void EnemyManager::SetParameter(char* name)
{
	ParameterRead* parameter = new ParameterRead;
	//parameter->SetJobParameter();
	EnemyParameter* enemy = parameter->GetEnemyParamList(name);


	memset(param_->name_, 0, sizeof(param_->name_));
	memcpy(param_->name_, enemy->GetName(), sizeof(param_->name_));

	param_->hp_ = enemy->GetHP();
	param_->def_ = enemy->GetDefence();
	param_->moveSpeed_ = enemy->GetMoveSpeed();
	param_->weight_ = enemy->GetWeight();
	param_->atk_ = enemy->GetAtk();
	param_->attackReach_ = enemy->GetAttackReach();
	param_->scale_ = enemy->GetScale();

	m_Scale = D3DXVECTOR3(param_->scale_, param_->scale_, param_->scale_);
	ownWeight_ = param_->weight_;
	hp_ = param_->hp_;

}

//
//	@brief	モデルの設定
void EnemyManager::SetModel(CD3DXSKINMESH* mesh)
{
	mesh_ = mesh;
}

//
//	@brief	バス停セット
void EnemyManager::SetBusStop(std::vector<D3DXVECTOR3> pos)
{
	busStop_ = pos;
	Collision* col = new Collision;
	for (auto p : pos)
	{
		int no = col->SetSpaceNo(p);
		busStopSpaceNo_.push_back(no);
	}
	//delete col;
	//col = nullptr;
}

//
//	@brief　			ターゲット設定
//	@param (chara)		ターゲットにするキャラ
void EnemyManager::SetTarget(CharactorManager* chara)
{
	targetChar_ = chara;
	
}

//
//	@brief	ターゲット座標セット
void EnemyManager::SetTargetPos(D3DXVECTOR3 pos)
{
	targetPos_ = pos;

	for (auto no : busStopSpaceNo_)
	{
		if (collision_->CheckSpaceNo(spaceNo_, no))
		{
			return;
		}
	}

	float dist = pow(m_Pos.x - targetPos_.x, 2) + pow(m_Pos.z - targetPos_.z, 2);
	float degree = D3DXToDegree(m_Yaw);
	D3DXVECTOR3 vec = targetPos_ - m_Pos;
	float angle = (atan2(vec.z, vec.x)*-1) - (D3DX_PI / 2.0f);
	angle = D3DXToDegree(angle);

	for (auto p : busStop_)
	{
		float temp = pow(m_Pos.x - p.x, 2) + pow(m_Pos.z - p.z, 2);
		D3DXVECTOR3 tempVec = p - m_Pos;
		float tempAngle = (atan2(tempVec.z, tempVec.x)*-1) - (D3DX_PI / 2.0f);
		tempAngle = D3DXToDegree(tempAngle);
		if (temp < dist && fabsf(degree - angle) <= 90)
		{
			targetPos_ = p;
			dist = temp;
		}
	}

	
}

//
//	@brief　					ターゲットの更新
//	@param (chara)			プレイヤー
//	@param (princess)		姫
void EnemyManager::Target_Update(CharactorManager * chara, CharactorManager * princess)
{
	CharactorManager* temp = targetChar_;
	//float dist = 5;

	if (perpetrator_ == chara->GetCharaType())
	{
		temp = chara;
	}

	////現在のターゲットが姫
	//if (targetChar_->GetCharaType() == princess->GetCharaType())
	//{
	//	if (collision_->CharaNear(m_Pos, chara->m_Pos, dist))
	//	{
	//		temp = chara;
	//	}
	//}

	//ターゲットが死んでいる
	if (!targetChar_->GetAliveFlg())
	{
		temp = princess;
	}

	//ターゲットの更新
	SetTarget(temp);
	SetTargetPos(temp->m_Pos);
}

//
//	@brief　			ターゲットポジションの更新
//	@param (position)	座標
void EnemyManager::SetTargetChar(CharactorManager* checkChar, CharactorManager* princess)
{
	////現在のターゲットとチェックするプレイヤーが一致するか
	//if (targetChar_->GetCharaType() == checkChar->GetCharaType())
	//{
	//	//チェックする(現在ターゲットのプレイヤー）が生存しているか
	//	if (checkChar->GetAliveFlg())
	//	{
	//		//ターゲット更新
	//		targetChar_ = checkChar;
	//		targetPos_ = targetChar_->m_Pos;
	//	}
	//	else
	//	{
	//		//ターゲットを姫に変更
	//		targetChar_ = princess;
	//		targetPos_ = targetChar_->m_Pos;
	//	}
	//}
	//else if (targetChar_->GetCharaType() == princess->GetCharaType()/* || targetChar_ == nullptr*/)       //現在のターゲットが姫
	//{
	//	//近くに生きているプレイヤーがいるかどうか(チェックするプレイヤーが生きている 且つ 距離が一定以内)
	//	if (checkChar->GetAliveFlg() && collision_->CharaNear(m_Pos, checkChar->m_Pos, 50.0))
	//	{
	//		//ターゲットをプレイヤーに変更
	//		targetChar_ = checkChar;
	//		targetPos_ = targetChar_->m_Pos;
	//	}
	//	else         //近くに生きているプレイヤーがいない
	//	{
	//		//ターゲット更新
	//		targetChar_ = princess;
	//		targetPos_ = targetChar_->m_Pos;
	//	}
	//}

	////if (!targetChar_->GetAliveFlg())
	////{
	////	targetChar_ = princess;
	////	targetPos_ = targetChar_->m_Pos;
	////}
}

//
//	@brief			移動処理
//	@param (speed)	移動速度
void EnemyManager::Move(float speed)
{
	if (knockBackFlg_)
	{
		KnockBack(knockBackPos_, knockBackDis_, knockBackSpeed_);
		return;
	}

	D3DXVECTOR3 E_Lock;
	E_Lock.x = targetPos_.x - m_Pos.x;
	E_Lock.z = targetPos_.z - m_Pos.z;

	D3DXVec3Normalize(&E_Lock, &E_Lock);

	//回転処理
	Rotation(E_Lock);

	//向いている角度から単位ベクトルを取得
	D3DXVECTOR3 vec = D3DXVECTOR3(sinf(m_Yaw)*-1, 0, cosf(m_Yaw)*-1);
	//D3DXVECTOR3 vec = E_Lock;
	float sp = speed;
	//opponentWeight_ = 1;
	m_Dir = D3DXVECTOR3(vec.x*sp*opponentWeight_, 0, vec.z*sp*opponentWeight_);

	if (motionNo_ != motion_->GetMotion("walk")->id_)
	{
		ChangeMotion(motion_, "walk");
		//motionNo_ = motion_->GetMotion("walk")->id_;
		//mesh_->m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//motionSpeed_ = 1 / (float)motion_->GetMotion("walk")->frame_;
	}

}

//
//	@brief	ダメージ計算
void EnemyManager::DamageCalc(unsigned int atk)
{

	float damage = atk / (1 + ((float)param_->def_ / 100));
	hp_ -= damage;

	if (hp_ <= 0 || param_->hp_ < hp_)
	{
		hp_ = 0;
		aliveFlg_ = false;
	}
}

//
//	@brief	死亡処理
void EnemyManager::Dead()
{
}

//
//	@brief	敵通常攻撃
void EnemyManager::Attack()
{
	float atkableDist = 2;//param_->attackReach_;
	int time = 3;

	if (collision_->CharaNear(m_Pos, targetPos_, atkableDist))
	{
		if (++atkWaitTime_ % (FPS*time) == 0)
		{
			moveAbleFlg_ = false;
			NormalAttack();
		}
		else
		{
			moveAbleFlg_ = true;
		}
	}
	else
	{
		moveAbleFlg_ = true;
		atkWaitTime_ = 0;
	}
}
