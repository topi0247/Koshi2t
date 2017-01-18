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
//	@brief モデル読み込み・初期化
void EnemyManager::CharaInit(char* name)
{
	mesh_ = new CD3DXSKINMESH;
	//mesh_ = creator_->LoadChara(name);

	//XFileRead* xfileRead = new XFileRead;
	MotionRead* motionRead = new MotionRead;
	//XFile* xfile = xfileRead->GetXFile(name);
	//CreateFromX(xfile->GetFilePath());
	SetMotionData(motionRead->GetMotionUser(name));
	SetParameter(name);
	motionPlayPos_ = 0.0f;
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
		if (!collision_->CheckSpaceNo(spaceNo_, no))
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
		if (temp < dist && fabsf(degree - angle) <= 45)
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

////
////	@brief　			ターゲットポジションの更新
////	@param (position)	座標
//void EnemyManager::SetTargetChar(CharactorManager* checkChar, CharactorManager* princess)
//{
//	////現在のターゲットとチェックするプレイヤーが一致するか
//	//if (targetChar_->GetCharaType() == checkChar->GetCharaType())
//	//{
//	//	//チェックする(現在ターゲットのプレイヤー）が生存しているか
//	//	if (checkChar->GetAliveFlg())
//	//	{
//	//		//ターゲット更新
//	//		targetChar_ = checkChar;
//	//		targetPos_ = targetChar_->m_Pos;
//	//	}
//	//	else
//	//	{
//	//		//ターゲットを姫に変更
//	//		targetChar_ = princess;
//	//		targetPos_ = targetChar_->m_Pos;
//	//	}
//	//}
//	//else if (targetChar_->GetCharaType() == princess->GetCharaType()/* || targetChar_ == nullptr*/)       //現在のターゲットが姫
//	//{
//	//	//近くに生きているプレイヤーがいるかどうか(チェックするプレイヤーが生きている 且つ 距離が一定以内)
//	//	if (checkChar->GetAliveFlg() && collision_->CharaNear(m_Pos, checkChar->m_Pos, 50.0))
//	//	{
//	//		//ターゲットをプレイヤーに変更
//	//		targetChar_ = checkChar;
//	//		targetPos_ = targetChar_->m_Pos;
//	//	}
//	//	else         //近くに生きているプレイヤーがいない
//	//	{
//	//		//ターゲット更新
//	//		targetChar_ = princess;
//	//		targetPos_ = targetChar_->m_Pos;
//	//	}
//	//}
//
//	////if (!targetChar_->GetAliveFlg())
//	////{
//	////	targetChar_ = princess;
//	////	targetPos_ = targetChar_->m_Pos;
//	////}
//}

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
	D3DXVECTOR3 dir;
	float sp = speed;
	//opponentWeight_ = 1;
	m_Dir = D3DXVECTOR3(vec.x*sp*opponentWeight_, 0, vec.z*sp*opponentWeight_);

	//進行方向にキャラがいなかったら進む。いたら滑って進む
	if (opponentWeight_ != 0)
		 {
				//opponentWeight_ = 1;
			dir = D3DXVECTOR3(vec.x*sp*opponentWeight_, 0, vec.z*sp*opponentWeight_);
		}
	else
		 {
		float fDistance = 0;
		D3DXVECTOR3 vNormal = m_Pos;
		collision_->SlideVector(&vec, vec, vNormal);
		dir = D3DXVECTOR3(vec.x*sp, 0, vec.z*sp);
		}
	
		m_Dir = dir;
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

	if (collision_->CharaNear(m_Pos, targetChar_->m_Pos, atkableDist)) 
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

	/*if (!moveAbleFlg_ && motionNo_ != motion_->GetMotion("attack")->id_)
	{
		motionChange_ = false;
		ChangeMotion(motion_, "attack");
	}
	if (motionNo_ == motion_->GetMotion("attack")->id_ && ++motionCount_ > motion_->GetMotion("attack")->frame_)
	{
		motionChange_ = true;
	}*/
}

//
//	@brief	モーション遷移
void EnemyManager::ChangeMotion(Motion* motion, char* name)
{
	motionNo_ = motion->GetMotion(name)->id_;
	motionFrame_ = motion->GetMotion(name)->frame_;
	motionSpeed_ = 1 / (float)motionFrame_;
	motionSpeed_ *= 0.5f;
	motionCount_ = 0;
	motionPlayPos_ = 0;
	strcpy(motionName_, name);
}

//
//	@brief			描画
void EnemyManager::CharaRender()
{
	bool drawFlg = true;
	//if (charaType_ != Enemy)
	//{
	/*if (motionName_ == "walk")
	{
		ChangeMotion(motion_, "walk");
	}
	else if (motionName_ == "attack")
	{
		ChangeMotion(motion_, "attack");
	}*/

	mesh_->m_pD3dxMesh->ChangeAnimSet(motionNo_);
	LPD3DXANIMATIONCONTROLLER anim = mesh_->m_pD3dxMesh->m_pAnimController;
	//anim->SetTrackAnimationSet(0, mesh_->m_pD3dxMesh->m_pAnimSet[motionNo_]);
	anim->SetTrackPosition(0, motionPlayPos_);
	anim->AdvanceTime(motionSpeed_, NULL);
	motionPlayPos_ += motionSpeed_;
	//}
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
}
