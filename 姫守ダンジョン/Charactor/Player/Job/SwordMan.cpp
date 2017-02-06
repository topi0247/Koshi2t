//
//	@file	SwordMan.cpp
//	@brief	剣士クラス
//	@date	2016/11/21
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#include "./SwordMan.h"


SwordMan::SwordMan(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	chainCount_ = 0;
	atkMotion_[0] = "attack1";
	atkMotion_[1] = "attack2";
	atkMotion_[2] = "attack3";
	atkMotion_[3] = "attack4";
	atkMotion_[4] = "attack5";
	atkMotion_[5] = "attack6";

	atkEffect_[0] = "s_Atk1";
	atkEffect_[1] = "s_Atk2";
	atkEffect_[2] = "s_Atk3";
	atkEffect_[3] = "s_Atk4";
	atkEffect_[4] = "s_Atk5";
	atkEffect_[5] = "s_Atk6";

	atkFlg_ = false;

	//UI
	jobMarkUI_ = new TD_Graphics;
	jobUIPos_ = D3DXVECTOR2(0 + charaType*UI_INTERVAL + UI_SPACE, 910);
	D3DXVECTOR2 scale(136.5, 148);
	jobMarkUI_->Init(L"./UI/UI_Tex/icon_soldier.png",scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));

}

SwordMan::~SwordMan()
{
	delete jobMarkUI_;
	jobMarkUI_ = nullptr;
}


//
//	@brief	リセット
void SwordMan::Reset()
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
	chainCount_ = 0;
	m_Pos = D3DXVECTOR3(-2.25 + charaType_*1.5, 0, -10);
}


//
//	@brief	攻撃
void SwordMan::Attack()
{
	static int keyWait = 0;
	int maxKeyWait = 10;
	//static bool atkAble = true;
	if (!atkFlg_&& GamePad::checkInput(charaType_, GamePad::InputName::A))
	{
		keyWait = 0;
		//++attackCount_;
		atkNo_ = normalAtk;
		//atkAble = false;
		moveAbleFlg_ = false;
		Normal_Attack();
		//keyWait = 0;
	}
	else if (/*!atkAble && */!GamePad::checkInput(charaType_, GamePad::InputName::A))
	{
		atkFlg_ = false;
	}
	//else if (atkNo_ == normalAtk)
	//{
	//	attackCount_ = 0;
	//	motionCount_ = 0;
	//	atkNo_ = noAtk;
	//	Normal_Attack();
	//	hit = false;
	//	atkNo_ = noAtk;
	//	Special_Attack();
	//}
	else if (atkNo_ == noAtk)
	{
		if (++keyWait > maxKeyWait)
		{
			chainCount_ = 0;
		}
	}

	//if (!atkAble)
	//{
	//	if (++keyWait > maxKeyWait)
	//	{
	//		atkAble = true;
	//	}
	//}

	//else if (atkNo_ == charge)
	//{
	//	attackCount_ = 0;
	//	motionCount_ = 0;
	//	motionChange_ = true;
	//	atkNo_ = specialAtk;
	//}
	//unsigned int inputTime = playerParam_.chargeTime_;

	///* 修正の必要あり */
	//unsigned int inputTime = motionSpeed_;

	//if (0 < attackCount_ && attackCount_ <= inputTime)
	//{
	//	atkNo_ = normalAtk;
	//}


	if (atkNo_ == normalAtk)
	{
		if (++motionCount_ >= motionFrame_/*motion_->GetMotion(atkMotion_[chainCount_%ChainAmount])->frame_*/)
		{
			atkNo_ = noAtk;
			//attackCount_ = 0;
			++chainCount_;
			motionChange_ = true;
			moveAbleFlg_ = true;
			motionCount_ = 0;
		}
	}
}

//
//	@breif	通常攻撃
void SwordMan::Normal_Attack()
{
	if (motionChange_&& !atkFlg_)//&& motionNo_ != motion_->GetMotion(atkMotion_[chainCount_%ChainAmount])->id_)
	{
		atkFlg_ = true;
		Sound::getInstance().SE_play("S_NORMALATK");

		//=======//
		Effect::getInstance().Effect_Play(atkEffect_[chainCount_%ChainAmount], D3DXVECTOR3(m_Pos.x, m_Pos.y, m_Pos.z));
		Effect::getInstance().SetScale(atkEffect_[chainCount_%ChainAmount], 0.5f);
		float yaw = D3DXToDegree(m_Yaw) + 180;
		//float roll = D3DXToDegree(m_Roll) + 180;
		Effect::getInstance().SetRotation(atkEffect_[chainCount_%ChainAmount], D3DXVECTOR3(0, D3DXToRadian(yaw), 0));
		//Effect::getInstance().SetRotation("s_Atk", D3DXVECTOR3(0, 1, 0), m_Yaw - 90);
		//Effect::getInstance().SetRotation("s_Atk",D3DXVECTOR3(0, m_Yaw + 90,180));
		//=======//

		motionChange_ = false;
		ChangeMotion(motion_, atkMotion_[chainCount_%ChainAmount]);
		motionSpeed_ = 1 / ((float)motionFrame_*2);
		Normal_Attack_Collision();

		float speed = -0.1;
		D3DXVECTOR3 dir(sinf(m_Yaw)*speed, 0, cosf(m_Yaw)*speed);
		m_Dir = dir;
	}

	//if (++motionCount_ > motionFrame_)
	//{
	//	atkNo_ = noAtk;
	//	//attackCount_ = 0;
	//	++chainCount_;
	//	motionCount_ = 0;
	//	motionChange_ = true;
	//	moveAbleFlg_ = true;
	//}

	//=======//
	//Effect::getInstance().Update("s_Atk", D3DXVECTOR3(m_Pos.x, m_Pos.y, m_Pos.z));
	//Effect::getInstance().Draw();
	//=======//
}

//
//	@brief	通常攻撃当たり判定
void SwordMan::Normal_Attack_Collision()
{
	float degree = D3DXToDegree(m_Yaw);
	float atkDist = param_->attackReach_;
	float hitAngle = param_->attackRange_;
	float backDist = param_->knockbackDist_;
	float speed = param_->knockbackSpeed_;

	if (!aroundCharaList_.empty())
	{
		for (auto chara : aroundCharaList_)
		{
			if (collision_->CharaNear(m_Pos, chara->m_Pos, atkDist))
			{
				D3DXVECTOR3 vec = chara->m_Pos - m_Pos;
				D3DXVec3Normalize(&vec, &vec);
				float angle = (atan2(vec.z, vec.x)*-1) - (D3DX_PI / 2.0f);
				angle = D3DXToDegree(angle);

				if (fabsf(degree) - fabsf(angle) <= hitAngle
					|| fabsf(degree) - fabsf(angle) >= hitAngle)
				{
					chara->SetKnockBack(m_Pos, backDist, speed, charaType_);
					if (chara->GetCharaType() == Enemy)
					{
						//敵にダメージが入った時のSE
						Sound::getInstance().SE_play("S_DAMAGE_HIT");
						chara->DamageCalc(param_->normalAtk_);
					}
				}
			}
		}
	}
}

void SwordMan::DamageSound()
{
	Sound::getInstance().SE_play("S_DAMAGE");
}


//
//	@brief	死亡音再生
void SwordMan::DeadSound()
{
	Sound::getInstance().SE_play("S_DEAD");
}


//
//	@brief			描画
void SwordMan::CharaRender()
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

	////UI描画
	//UIRender();
}
