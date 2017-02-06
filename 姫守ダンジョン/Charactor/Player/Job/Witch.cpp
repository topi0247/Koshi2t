//
//	@file	Witch.cpp
//	@brief	魔導士クラス
//	@date	2016/11/21
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#include "./Witch.h"


Witch::Witch(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	magicFlg_ = false;
	chargeMotionFlg_ = false;
	atkNo_ = noAtk;
	attackCount_ = 0;
	magic_ = new CD3DXMESH;
	magicSpeed_ = 3.0f;
	magic_ = creator_->LoadStage("魔法球");

	//UI
	jobMarkUI_ = new TD_Graphics;
	jobUIPos_ = D3DXVECTOR2(0 + charaType*UI_INTERVAL + UI_SPACE, 910);
	D3DXVECTOR2 scale(136.5, 148);
	jobMarkUI_->Init(L"./UI/UI_Tex/icon_witch.png",scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	//Witch_UI["WITCH_UI"] = new TD_Graphics;
}

Witch::~Witch()
{
	delete magic_;
	magic_ = nullptr;
	delete jobMarkUI_;
	jobMarkUI_ = nullptr;
	//delete Witch_UI["WITCH_UI"];
	//magic_ = nullptr;
}



//
//	@brief	リセット
void Witch::Reset()
{
	hp_ = param_->hp_;
	motionCount_ = 0;
	motionChange_ = true;
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	aroundCharaList_.clear();
	allCharaList_.clear();
	atkNo_ = noAtk;
	revivalFlg_ = false;
	callTiming_ = 0;
	attackCount_ = 0;
	magicFlg_ = false;

	m_Pos = D3DXVECTOR3(-2.25 + charaType_*1.5, 0, -10);
}


//
//	@brief			移動処理
//	@param (speed)	移動速度
void Witch::Move(float speed)
{
	if (damageFlg_)
	{
		damageDrawTime_ = FPS * 0.5;
		if (damageCount_ >= damageDrawTime_)
		{
			moveAbleFlg_ = true;
			damageFlg_ = false;
			damageCount_ = 0;
		}
	}

	if (knockBackFlg_ == true)
	{
		KnockBack(knockBackPos_, knockBackDis_, knockBackSpeed_);
		if (motionNo_ != motion_->GetMotion("wait")->id_)
		{
			ChangeMotion(motion_, "wait");
		}
		return;
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

	if (!moveAbleFlg_)
	{
		return;
	}

	//移動
	const float moveEpsilon = 0.2;	//誤作防止用
	float sp = 0;
	if (fabsf(inputStick.x) > moveEpsilon || fabsf(inputStick.z) > moveEpsilon)
	{
		sp = speed;

		if (motionChange_ == true && motionNo_ != motion_->GetMotion("walk")->id_)
		{
			ChangeMotion(motion_, "walk");
		}
	}
	else
	{
		if (motionChange_ == true && motionNo_ != motion_->GetMotion("wait")->id_)
		{
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
//	@brief	攻撃
void Witch::Attack()
{
	if (/*magicFlg_ == false && */GamePad::checkInput(charaType_, GamePad::InputName::A)
		/*|| GetKeyState('1') & 0x80*/)
	{
		++attackCount_;
		//atkNo_ = waitAtk;
		moveAbleFlg_ = false;

	}
	else if (atkNo_ == normalAtk)
	{
		attackCount_ = 0;
		Normal_Attack();
	}
	else if (atkNo_ == charge)
	{
		attackCount_ = 0;
		atkNo_ = specialAtk;
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = FPS*param_->chargeTime_;

	if (0 < attackCount_ && attackCount_ <= inputTime)
	{
		atkNo_ = normalAtk;
	}
	else if (inputTime < attackCount_)
	{
		atkNo_ = charge;
		moveAbleFlg_ = false;
		if (!chargeMotionFlg_ && motionNo_ != motion_->GetMotion("charge1")->id_)
		{
			motionChange_ = false;
			chargeMotionFlg_ = true;
			//motionNo_ = motion_->GetMotion("charge")->id_;
			//m_pD3dxMesh->ChangeAnimSet(motionNo_);
			//timeEnd_ = motion_->GetMotion("attack")->frame_;
			//motionSpeed_ = 1 / (float)timeEnd_;
			//motionCount_ = 0;
			ChangeMotion(motion_, "charge1");
			Sound::getInstance().SE_play("M_CHARGE");
			Effect::getInstance().Effect_Play("charge2", m_Pos);
		}
		else if (++motionCount_ > motion_->GetMotion("charge1")->frame_
			&& chargeMotionFlg_ &&  motionNo_ != motion_->GetMotion("charge2")->id_)
		{
			ChangeMotion(motion_, "charge2");
		}
	}

	if (atkNo_ == specialAtk)
	{
		chargeMotionFlg_ = false;
		Special_Attack();
		Effect::getInstance().Effect_Stop("charge2");
		Sound::getInstance().SE_stop("M_CHARGE");
	}
	if (!magicFlg_)
	{
		ballFlg_ = false;
		arrowFlg_ = false;
		//moveAbleFlg_ = true;
	}
}

//
//	@brief	通常攻撃
void Witch::Normal_Attack()
{
	//float dist = param_->attackReach_;
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("attack1")->id_)
	{
		motionChange_ = false;
		//motionNo_ = motion_->GetMotion("attack")->id_;
		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//timeEnd_ = motion_->GetMotion("attack")->frame_;
		//motionSpeed_ = 1 / (float)timeEnd_;
		//motionCount_ = 0;
		ChangeMotion(motion_, "attack1");
		InstanceMagicBall(param_->attackRange_, param_->normalAtk_, true);
		ballFlg_ = true;
		Effect::getInstance().Effect_Play("magicball", magicBall_->GetPosition());
		Effect::getInstance().SetScale("magicball", 0.2);
	}

	if (++motionCount_ > motionFrame_)
	{
		Sound::getInstance().SE_play("M_NORMALATK");
		atkNo_ = noAtk;
		motionChange_ = true;
		//moveAbleFlg_ = true;
	}
}

//
//	@brief	特殊攻撃
void Witch::Special_Attack()
{
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("attack1")->id_)
	{
		motionChange_ = false;
		//motionNo_ = motion_->GetMotion("attack")->id_;
		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//timeEnd_ = motion_->GetMotion("attack")->frame_;
		//motionSpeed_ = 1 / (float)timeEnd_;
		//motionCount_ = 0;
		ChangeMotion(motion_, "attack1");
		InstanceMagicBall(param_->attackRange_, param_->normalAtk_, false);
		arrowFlg_ = true;
		Effect::getInstance().Effect_Play("arrow", magicBall_->GetPosition());
		Effect::getInstance().SetRotation("arrow", D3DXVECTOR3(0, m_Yaw, 0));
	}

	if (++motionCount_ > motionFrame_)
	{
		Sound::getInstance().SE_stop("M_CHARGE");
		Sound::getInstance().SE_play("M_NORMALATK");
		atkNo_ = noAtk;
		motionChange_ = true;
		//moveAbleFlg_ = true;
		//Effect::getInstance().SetScale("arrow", 0.2);
		//RazorBeam();
	}
	

}

//
//	@brief	マジックボール生成
void Witch::InstanceMagicBall(float range, float atk, bool flg)
{
	//float kRange = param_->weaponHitReach_;
	float kDist = param_->knockbackDist_;
	float kSpeed = param_->knockbackSpeed_;
	if (!magicFlg_)
	{
		float angle = D3DXToDegree(m_Yaw);
		//for (int i = 0; i < magicBallCount_; i++)
		//{
		magicBall_ = new WeaponBall;
		/*int degree = 90 / (magicBallCount_ / 2 + 1);
		float temp = angle - 90 + degree + degree*i;
		temp = D3DXToRadian(temp);*/
		D3DXVECTOR3 vec(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);
		magicBall_->SetDir(vec);
		magicBall_->SetScale(0/*param_->weaponScale_*/);
		magicBall_->SetStartPos(D3DXVECTOR3(m_Pos.x, m_Pos.y + 1, m_Pos.z));
		//magicBall_->SetDamageList(allCharaList_, charaType_, 1);
		magicBall_->SetKnockBack(range, kDist, kSpeed, charaType_, Enemy);
		magicBall_->SetAttack(atk);
		magicBall_->SetHitSound("M_DAMAGE_HIT");
		magicBall_->SetHitDelFlg(flg);
		//}
		magicFlg_ = true;
	}
}

//
//	@brief	マジックボールの更新
void Witch::WeaponUpdate()
{
	if (magicFlg_)
	{
		magicBall_->Move_Weapon(magicSpeed_);
		//magicBall_->SetDamageList(allCharaList_, charaType_, 1);
		if (ballFlg_)
		{
			Effect::getInstance().Update("magicball", magicBall_->GetPosition());
		}
		else if (arrowFlg_)
		{
			Effect::getInstance().Update("arrow", magicBall_->GetPosition());
		}
		if (magicBall_->GetDelFlg())
		{
			magicFlg_ = false;
			delete magicBall_;
			magicBall_ = nullptr;
			//Effect::getInstance().Effect_Stop("magicball");
			moveAbleFlg_ = true;
		}
	}

}

////
////	@brief	レーザービーム
//void Witch::RazorBeam()
//{
//	magicSpeed_ = 1.0f;
//	float kRange = param_->weaponHitReach_;
//	float kDist = param_->knockbackDist_;
//	float kSpeed = param_->knockbackSpeed_;
//	if (!magicFlg_)
//	{
//		magicBall_ = new WeaponBall;
//		D3DXVECTOR3 vec(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);
//		magicBall_->SetDir(vec);
//		magicBall_->SetScale(0);
//		magicBall_->SetStartPos(D3DXVECTOR3(m_Pos.x, m_Pos.y, m_Pos.z));
//		//magicBall_->SetDamageList(allCharaList_, charaType_, 1);
//		magicBall_->SetKnockBack(kRange, kDist, kSpeed, charaType_,Enemy);
//		magicBall_->SetAttack(param_->specialAtk_);
//		magicBall_->SetHitSound("M_DAMAGE_HIT");
//		magicBall_->SetHitDelFlg(false);
//
//		magicFlg_ = true;
//	}
//}

//
//	@brief	被ダメ時のSE再生
void Witch::DamageSound()
{
	Sound::getInstance().SE_play("M_DAMAGE");
}

//
//	@brief	死亡音再生
void Witch::DeadSound()
{
	Sound::getInstance().SE_play("M_DEAD");
}

//
//	@brief	描画
void Witch::CharaRender()
{
	//モーション番号セット
	mesh_->m_pD3dxMesh->ChangeAnimSet(motionNo_);
	//再生地点をセット
	LPD3DXANIMATIONCONTROLLER anim = mesh_->m_pD3dxMesh->m_pAnimController;
	anim->SetTrackPosition(0, motionPlayPos_);
	//再生
	anim->AdvanceTime(motionSpeed_, NULL);
	//再生地点の更新
	motionPlayPos_ += motionSpeed_;

	//モデル描画
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
	//魔法描画
	if (magicFlg_)
	{
		magic_->Render(magicBall_->GetPosition(), D3DXVECTOR3(0, 0, 0), magicBall_->GetScale());
	}

	//Effect::getInstance().Draw();

	////UI描画
	//UIRender();
}