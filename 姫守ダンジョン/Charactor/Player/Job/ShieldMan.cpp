//
//	@file	ShieldMan.cpp
//	@brief	盾士クラス
//	@date	2016/11/21
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#include "ShieldMan.h"

ShieldMan::ShieldMan(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	spMoveFlg_ = false;
	effectFlg_ = false;
	shield_ = new CD3DXMESH;
	shield_ = creator_->LoadStage("盾");
	//ShieldMan_UI["SHIELDMAN_UI"] = new TD_Graphics;

	//UI
	jobMarkUI_ = new TD_Graphics;
	jobUIPos_ = D3DXVECTOR2(0 + charaType*UI_INTERVAL + UI_SPACE, 910);
	D3DXVECTOR2 scale(136.5, 148);
	jobMarkUI_->Init(L"./UI/UI_Tex/icon_knight.png", scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));

}

ShieldMan::~ShieldMan()
{
	SAFE_DELETE(shield_);
	delete jobMarkUI_;
	jobMarkUI_ = nullptr;
	//delete ShieldMan_UI["SHIELDMAN_UI"];
}

//
//	@brief	リセット
void ShieldMan::Reset()
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
	spMoveFlg_ = false;

	m_Pos = D3DXVECTOR3(-2.25 + charaType_*1.5, 0, -10);
	//ShieldMan_UI["SHIELDMAN_UI"]->Init(L"./UI/UI_Tex/UISeeld.png", 0, D3DXVECTOR2(15, 785), D3DXVECTOR2(256, 128), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
}

//
//	@brief	攻撃
void ShieldMan::Attack()
{
	if (GamePad::checkInput(charaType_, GamePad::InputName::A)
		/*|| GetKeyState('1') & 0x80*/)
	{
		++attackCount_;
		moveAbleFlg_ = false;
	}
	else if (atkNo_ == normalAtk)
	{
		attackCount_ = 0;
		Normal_Attack();
		//if (++motionCount_ > motionFrame_)
		//{
		//	atkNo_ = noAtk;
		//	//attackCount_ = 0;
		//	motionCount_ = 0;
		//	motionChange_ = true;
		//	moveAbleFlg_ = true;
		//	ChangeMotion(motion_, "wait");
		//}

	}
	else
	{
		spMoveFlg_ = false;
		moveAbleFlg_ = true;
		attackCount_ = 0;
		atkNo_ = noAtk;
		spMove_ = D3DXVECTOR3(1, 0, 1);
		/*if (!motionChange_&&motionNo_ != motion_->GetMotion("wait")->id_)
		{
			ChangeMotion(motion_, "wait");
			motionChange_ = true;

		}*/
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = FPS*param_->chargeTime_;
	//unsigned int tempFrame = motion_->GetMotion("special")->frame_;

	if (0 < attackCount_ && attackCount_ <= inputTime)
	{
		atkNo_ = normalAtk;
	}
	else if (inputTime < attackCount_ /*&& attackCount_ - inputTime < tempFrame*/)
	{
		atkNo_ = specialAtk;
		spMoveFlg_ = true;
	}

	/*
		if (atkNo_ == normalAtk)
		{
			if (++motionCount_ >= motionFrame_)
			{
				atkNo_ = noAtk;
				motionChange_ = true;
				moveAbleFlg_ = true;
				motionCount_ = 0;
			}
		}
		else */if (atkNo_ == specialAtk)
		{
			moveAbleFlg_ = true;
			Special_Attack();
		}
}

//
//	@brief	通常攻撃
void ShieldMan::Normal_Attack()
{
	float hitAngle = param_->attackRange_;
	float atk = param_->normalAtk_;
	//Normal_Attack_Collision();
	if (motionChange_ && motionNo_ != motion_->GetMotion("attack1")->id_)
	{
		Sound::getInstance().SE_play("Sh_NORMALATK");

		motionChange_ = false;
		//motionNo_ = motion_->GetMotion("attack1")->id_;
		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//timeEnd_ = motion_->GetMotion("attack1")->frame_;
		//motionSpeed_ = 1 / (float)timeEnd_;
		//motionCount_ = 0;
		ChangeMotion(motion_, "attack1");

		Attack_Collision(atk, hitAngle);

	}

	if (++motionCount_ >= motionFrame_)
	{
		atkNo_ = noAtk;
		//attackCount_ = 0;
		motionChange_ = true;
		moveAbleFlg_ = true;
	}
}

//
//	@brief	特殊攻撃
void ShieldMan::Special_Attack()
{
	//spMove_ = D3DXVECTOR3(param_->specialMoveSpeed_, param_->specialMoveSpeed_, param_->specialMoveSpeed_);
	//Special_Attack_Collision();
	float hitAngle = param_->specialAtkRange_;
	float atk = param_->specialAtk_;
	Attack_Collision(atk, hitAngle);
	if (spMoveFlg_ == false)
	{
		if (motionNo_ != motion_->GetMotion("special")->id_)
		{
			motionChange_ = false;
			//motionNo_ = motion_->GetMotion("special")->id_;
			//m_pD3dxMesh->ChangeAnimSet(motionNo_);
			//motionSpeed_ = 1 / (float)motion_->GetMotion("special")->frame_;
			ChangeMotion(motion_, "special");
		}
	}
	//if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("special")->id_)
	//{
	//	motionChange_ = false;
	//	motionNo_ = motion_->GetMotion("special")->id_;
	//	m_pD3dxMesh->ChangeAnimSet(motionNo_);
	//	timeEnd_ = motion_->GetMotion("special")->frame_;
	//	motionSpeed_ = 1 / (float)timeEnd_;
	//	motionCount_ = 0;
	//}

	//if (++motionCount_ > timeEnd_)
	//{
	//	atkNo_ = noAtk;
	//	//attackCount_ = 0;
	//	motionChange_ = true;
	//	motionCount_ = 0;
	//	hit = false;
	//}

}

//
//	@brief	攻撃の当たり判定
void ShieldMan::Attack_Collision(float atk, float hitAngle)
{
	float degree = D3DXToDegree(m_Yaw);
	//float hitAngle = param_->attackRange_;
	float atkDist = param_->attackReach_;
	float backSpeed = param_->knockbackSpeed_;

	float backDist = 0;
	if (atkNo_ == normalAtk)
	{
		backDist = param_->knockbackDist_;
	}
	else
	{
		backDist = 0.8;
	}



	if (!aroundCharaList_.empty())
	{
		for (auto chara : aroundCharaList_)
		{
			if (collision_->CharaNear(m_Pos, chara->m_Pos, atkDist))
			{
				D3DXVECTOR3 vec = chara->m_Pos - m_Pos;
				float angle = (atan2(vec.z, vec.x)*-1) - (D3DX_PI / 2.0f);
				angle = D3DXToDegree(angle);

				//float tempAngle = 360;
				if (fabsf(degree - angle) <= hitAngle)
				{
					chara->SetKnockBack(m_Pos, backDist, backSpeed, charaType_);
					if (chara->GetCharaType() == Enemy && atkNo_ == normalAtk)
					{
						chara->DamageCalc(atk);

						//敵にダメージが入った時のSE
						Sound::getInstance().SE_play("Sh_DAMAGE_HIT");
					}
				}
			}
		}
	}
}


//
//	@brief	ダメージ計算
void ShieldMan::DamageCalc(unsigned int atk)
{
	if (!damageFlg_)
	{
		Sound::getInstance().SE_play("Sh_DAMAGE");
		damageFlg_ = true;

		float damage = 0;
		float constant = 20;
		if (atkNo_ != specialAtk)
		{
			damage = atk / (1 + ((float)param_->def_ / 100));
		}
		else
		{
			damage = constant;
		}

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
//	@brief			移動処理
//	@param (speed)	移動速度
void ShieldMan::Move(float speed)
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

	if (atkNo_ == specialAtk)
	{
		knockBackFlg_ = false;
		moveAbleFlg_ = true;
	}

	if (knockBackFlg_ == true)
	{
		KnockBack(knockBackPos_, knockBackDis_, knockBackSpeed_);
		return;
	}

	//スティックの傾き取得
	D3DXVECTOR3 inputStick;
	inputStick.x = GamePad::getAnalogValue(charaType_, GamePad::AnalogName::AnalogName_LeftStick_X);
	inputStick.z = GamePad::getAnalogValue(charaType_, GamePad::AnalogName::AnalogName_LeftStick_Y);

	//回転処理
	if (atkNo_ != specialAtk)
	{
		const float rotEpsilon = 0.3;
		if (fabsf(inputStick.x) > rotEpsilon || fabsf(inputStick.z) > rotEpsilon)
		{
			Rotation(inputStick);
		}
	}


	//移動
	const float moveEpsilon = 0.2;	//誤作防止用
	float sp = 0;
	if (fabsf(inputStick.x) > moveEpsilon || fabsf(inputStick.z) > moveEpsilon)
	{
		if (atkNo_ != specialAtk)
		{
			sp = speed;
		}
		else
		{
			sp = param_->specialMoveSpeed_;
		}

		if (motionChange_ == true)
		{
			if (atkNo_ != specialAtk && motionNo_ != motion_->GetMotion("walk")->id_)
			{
				ChangeMotion(motion_, "walk");
			}
			else if (atkNo_ == specialAtk && motionNo_ != motion_->GetMotion("specialWalk")->id_)
			{
				ChangeMotion(motion_, "specialWalk");
			}
			if (atkNo_ == specialAtk)
			{
				Sound::getInstance().SE_play("Sh_SPECIAL");
				if (!effectFlg_)
				{
					Effect::getInstance().Effect_Play("smork", m_Pos + m_Dir);
					Effect::getInstance().SetRotation("smork", D3DXVECTOR3(0, m_Yaw, 0));
					effectFlg_ = true;
				}
			}
		}
		if (effectFlg_ && ++motionCount_ % 10 == 0)
		{
			effectFlg_ = false;
		}
	}
	else
	{
		if (motionChange_ == true)
		{
			if (atkNo_ != specialAtk&& motionNo_ != motion_->GetMotion("wait")->id_)
			{
				ChangeMotion(motion_, "wait");
				effectFlg_ = false;
			}
			else if (atkNo_ == specialAtk&&motionNo_ != motion_->GetMotion("specialwait")->id_)
			{
				ChangeMotion(motion_, "specialwait");
			}
		}
	}



	//opponentWeight_ = 1;

	MoveCharaHit();

	m_Dir = D3DXVECTOR3(inputStick.x*sp * opponentWeight_, 0, inputStick.z*sp * opponentWeight_);
	////=======//
	//if (effectFlg_)
	//{
	//	//Effect::getInstance().SetScale("smork", 0.09f);
	//	effectFlg_ = false;
	//}
	////=======//

	//m_vPos += D3DXVECTOR3(inputStick.x*sp - opponentWeight_, 0, inputStick.z*sp - opponentWeight_);

	GamePad::update();

	//m_Dir = D3DXVECTOR3(m_AxisX.x, m_AxisY.y, m_AxisZ.z);
	//m_Dir = D3DXVECTOR3(m_Move.x, 0, m_Move.z);

	//=======//
	//Effect::getInstance().Draw();
	//=======//

}


//
//	@brief	死亡音再生
void ShieldMan::DeadSound()
{
	Sound::getInstance().SE_play("Sh_DEAD");
}

//
//	@brief	描画
void ShieldMan::CharaRender()
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

	float scale = 0.2f;
	if (drawFlg)
	{
		//float scale = 0.2f;
		mesh_->Render(m_Pos, m_Yaw, D3DXVECTOR3(scale, scale, scale));
	}
	//盾の描画
	if (atkNo_ == specialAtk && aliveFlg_)
	{
		float yaw = D3DXToDegree(m_Yaw) + 50.0f;
		float dist = -0.8;
		yaw = D3DXToRadian(yaw);
		D3DXVECTOR3 pos(sinf(yaw)*dist, 0, cosf(yaw) * dist);
		pos += m_Pos;
		shield_->Render(pos, D3DXVECTOR3(0, yaw, 0), scale);
		yaw = D3DXToDegree(m_Yaw) - 50.0f;
		yaw = D3DXToRadian(yaw);
		pos = D3DXVECTOR3(sinf(yaw)*dist, 0, cosf(yaw) * dist);
		pos += m_Pos;
		shield_->Render(pos, D3DXVECTOR3(0, yaw, 0), scale);
	}

	////UI描画
	//UIRender();
}
