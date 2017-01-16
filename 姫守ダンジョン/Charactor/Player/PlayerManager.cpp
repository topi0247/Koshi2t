//
//	@file	PlayerManager.cpp
//	@brief	プレイヤー管理クラス
//	@date	2016/11/09
//	@author	仁科香苗

#include "PlayerManager.h"

//
//	@brief	コンストラクタ
PlayerManager::PlayerManager()
{
	revivalFlg_ = false;
	callTiming_ = 0;
}


void PlayerManager::SetParameter(char* name)
{
	ParameterRead* parameter = new ParameterRead;
	//parameter->SetJobParameter(/*"./../ReadData/JobParameterData.csv"*/);
	JobParameter* job = parameter->GetJobParamList(name);


	memset(param_->name_, 0, sizeof(param_->name_));
	memcpy(param_->name_, job->GetName(), sizeof(param_->name_));

	param_->hp_ = job->GetHP();
	param_->normalAtk_ = job->GetNormalAtk();
	param_->specialAtk_ = job->GetSpAtk();
	param_->def_ = job->GetDefence();
	param_->chainWeapon_ = job->GetChainWeapon();
	param_->spChainWeapon_ = job->GetSpChainWeapon();
	param_->specialAttackTime_ = job->GetSpAtkTime();
	param_->invisibleTime_ = job->GetInvisivleTime();
	param_->weaponDelTime_ = job->GetWeaponDelTime();
	param_->chargeTime_ = job->GetChargeTime();
	param_->moveSpeed_ = job->GetMoveSpeed();
	param_->specialMoveSpeed_ = job->GetSpMoveSpeed();
	param_->weight_ = job->GetWeight();
	param_->attackReach_ = job->GetAttackReach();
	param_->attackRange_ = job->GetAttackRange();
	param_->specialAtkRange_ = job->GetSpAtkRange();
	param_->scale_ = job->GetScale();
	param_->knockbackSpeed_ = job->GetKnockBackSpeed();
	param_->knockbackDist_ = job->GetKnockBackDist();
	param_->weaponScale_ = job->GetWeaponScale();
	param_->weaponHitReach_ = job->GetWeaponHitReach();
	param_->weaponDelDist_ = job->GetWeaponDelDist();

	m_Scale = D3DXVECTOR3(param_->scale_, param_->scale_, param_->scale_);
	ownWeight_ = param_->weight_;
	hp_ = param_->hp_;
}

//
//	@brief			移動処理
//	@param (speed)	移動速度
void PlayerManager::Move(float speed)
{
	if (damageFlg_)
	{
		damageDrawTime_ = FPS * 0.5;
		if (damageCount_ >= damageDrawTime_)
		{
			damageFlg_ = false;
			damageCount_ = 0;
		}
		else
		{
			if (knockBackFlg_)
			{
				KnockBack(knockBackPos_, knockBackDis_, knockBackSpeed_);
				//return;
			}
			return;
		}
	}



	//スティックの傾き取得
	D3DXVECTOR3 inputStick;
	inputStick.x = GamePad::getAnalogValue(charaType_, GamePad::AnalogName::AnalogName_LeftStick_X);
	inputStick.z = GamePad::getAnalogValue(charaType_, GamePad::AnalogName::AnalogName_LeftStick_Y);

	//回転処理
	const float rotEpsilon = 0.3;
	if (fabsf(inputStick.x) > rotEpsilon || fabsf(inputStick.z) > rotEpsilon)
	{
		Rotation(inputStick);
	}


	//移動
	const float moveEpsilon = 0.2;	//誤作防止用
	float sp = 0;
	if (fabsf(inputStick.x) > moveEpsilon || fabsf(inputStick.z) > moveEpsilon)
	{
		sp = speed;

		if (motionChange_ == true && motionNo_ != motion_->GetMotion("walk")->id_)
		{
			//motionNo_ = motion_->GetMotion("walk")->id_;
			//m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("walk")->id_);
			//モーション速度
			//motionSpeed_ = 1 / (float)motion_->GetMotion("walk")->frame_;
			ChangeMotion(motion_, "walk");
		}
	}
	else
	{
		if (motionChange_ == true && motionNo_ != motion_->GetMotion("wait")->id_)
		{
			//motionNo_ = motion_->GetMotion("wait")->id_;
			//m_pD3dxMesh->ChangeAnimSet(motionNo_);
			//motionSpeed_ = 1 / (float)motion_->GetMotion("walk")->frame_;
			ChangeMotion(motion_, "wait");
		}
	}

	//opponentWeight_ = 1;

	MoveCharaHit();

	m_Dir = D3DXVECTOR3(inputStick.x*sp * opponentWeight_, 0, inputStick.z*sp * opponentWeight_);
	//m_vPos += D3DXVECTOR3(inputStick.x*sp - opponentWeight_, 0, inputStick.z*sp - opponentWeight_);

	GamePad::update();

	//m_Dir = D3DXVECTOR3(m_AxisX.x, m_AxisY.y, m_AxisZ.z);
	//m_Dir = D3DXVECTOR3(m_Move.x, 0, m_Move.z);

}

//
//	@brief	ダメージ計算
void PlayerManager::DamageCalc(unsigned int atk)
{
	if (!damageFlg_)
	{
		damageFlg_ = true;
		DamageSound();
		float damage = atk / (1 + ((float)param_->def_ / 100));
		hp_ -= damage;

		if (hp_ <= 0 || param_->hp_ < hp_)
		{
			hp_ = 0;
			aliveFlg_ = false;
			damageFlg_ = false;
		}
	}
}

//
//	@brief	死亡処理
void PlayerManager::Dead()
{
	//aliveFlg_ = false;

	if (motionChange_ == true && motionNo_ != motion_->GetMotion("dead1")->id_ && motionNo_ != motion_->GetMotion("dead2")->id_)
	{
		moveAbleFlg_ = false;
		DeadSound();
		ChangeMotion(motion_, "dead1");
		motionCount_ = 0;
	}
	if (++motionCount_%motionFrame_ == 0 && motionNo_ == motion_->GetMotion("dead1")->id_)
	{
		ChangeMotion(motion_, "dead2");
		motionCount_ = 0;
		motionChange_ = true;
	}

}


//
//	@brief	復活
void PlayerManager::Revival()
{
	if (motionChange_ == true && motionNo_ != motion_->GetMotion("alive")->id_)
	{
		motionChange_ = false;
		//motionNo_ = motion_->GetMotion("alive")->id_;
		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//motionSpeed_ = 1 / (float)motion_->GetMotion("alive")->frame_;
		ChangeMotion(motion_, "alive");
	}

	if (motionNo_ == motion_->GetMotion("alive")->id_)
	{
		if (++motionCount_%motionFrame_ == 0)
		{
			moveAbleFlg_ = true;
			motionChange_ = true;
			motionCount_ = 0;
			hp_ = param_->hp_;
			revivalFlg_ = false;
			aliveFlg_ = true;
		}
	}
}

//
//	@brief	姫呼び
void PlayerManager::Princess_Call()
{
	//static int pushButtonTime = 0;
	static bool callFlg = false;
	if (GamePad::checkInput(charaType_, GamePad::InputName::B) && atkNo_ == noAtk)
	{
		//++pushButtonTime;
		callFlg = true;
		moveAbleFlg_ = false;
		callPos_ = m_Pos;
		callTiming_ = clock();
		if (motionNo_ != motion_->GetMotion("call1")->id_ && motionNo_ != motion_->GetMotion("call2")->id_)
		{
			moveAbleFlg_ = false;
			motionChange_ = false;
			ChangeMotion(motion_, "call1");
		}
	}
	else if (callFlg && !moveAbleFlg_)
	{
		callFlg = false;
		ChangeMotion(motion_, "call3");
	}

	if (callFlg&&motionNo_ == motion_->GetMotion("call1")->id_)
	{
		if (++motionCount_ > motionFrame_)
		{
			ChangeMotion(motion_, "call2");
		}
	}
	else if (motionNo_ == motion_->GetMotion("call3")->id_)
	{
		if (++motionCount_ > motionFrame_)
		{
			//revivalFlg_ = false;
			moveAbleFlg_ = true;
			motionChange_ = true;
			ChangeMotion(motion_, "wait");
		}
	}
	//if (0 < pushButtonTime)
	//{
	//	if (motionChange_ == true && motionNo_ != motion_->GetMotion("call1")->id_)
	//	{
	//		motionChange_ = false;
	//		//motionNo_ = motion_->GetMotion("call")->id_;
	//		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
	//		//motionSpeed_ =  1/(float)motion_->GetMotion("call")->frame_;
	//		ChangeMotion(motion_, "call1");
	//	}
	//}
	//else if (motion_->GetMotion("call1")->frame_ < pushButtonTime)
	//{
	//	if (motionChange_ == true && motionNo_ != motion_->GetMotion("call2")->id_)
	//	{
	//		ChangeMotion(motion_, "call2");
	//	}
	//}

	
}

//
//	@breif	復活フラグセット
void PlayerManager::SetRevivalFlg()
{
	revivalFlg_ = true;
}

//
//	@brief	生存フラグ取得
bool PlayerManager::GetAliveFlg()const
{
	return aliveFlg_;
}

//
//	@brief	姫を呼んだクロック時間取得
double PlayerManager::GetCallTiming()const
{
	return callTiming_;
}

//
//	@brief	姫を呼んだ瞬間の座標取得
D3DXVECTOR3 PlayerManager::GetCallPos()const
{
	return callPos_;
}