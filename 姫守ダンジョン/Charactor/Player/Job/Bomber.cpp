//
//	@file	Bomber.cpp
//	@brief	”š’eŽmƒNƒ‰ƒX
//	@date	2016/11/21
//	@author	m‰È•c
//	@author	‹g‰z‘å‹R(ƒTƒEƒ“ƒh)

#include "./Bomber.h"

Bomber::Bomber(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	bombFlg_ = false;
	bombList_.clear();
	bombScale_ = 1;
	bombCount_ = 1;
	invisibleCount_ = 0;
	invinsibleFlg_ = false;
	bomb_ = new CD3DXMESH;
	bomb_ = creator_->LoadStage("”š’e");

	//UI
	jobMarkUI_ = new TD_Graphics;
	jobUIPos_ = D3DXVECTOR2(30 + charaType*UI_INTERVAL + UI_SPACE, 860);
	D3DXVECTOR2 scale(105, 100);
	jobMarkUI_->Init(L"./UI/UI_Tex/bomber.png", jobUIPos_, scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));


}

Bomber::~Bomber()
{
	delete bomb_;
	bomb_ = nullptr;
	delete jobMarkUI_;
	jobMarkUI_ = nullptr;
	//delete bom_UI["BOM_UI"];
	//bomb_ = nullptr;
}


////
////	@brief						Xƒtƒ@ƒCƒ‹“Ç‚Ýž‚Ý
////	@param (m_hWnd)				ƒEƒBƒ“ƒhƒEƒnƒ“ƒhƒ‹
////	@param (m_pDevice)			ƒfƒoƒCƒX
////	@param (m_pDeviceContext)	ƒfƒoƒCƒXƒRƒ“ƒeƒLƒXƒg
////	@param (fileName)			“Ç‚Ýž‚ÞƒLƒƒƒ‰–¼
//const char* Bomber::CharaInit(const char* fileName)
//{
//	bomb_->Init("bomb.x");
//
//	bom_UI["BOM_UI"]->Init(L"./UI/UI_Tex/UIbom.png", 0, D3DXVECTOR2(1480, 785), D3DXVECTOR2(256, 128), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
//
//	char FileName[80] = { 0 };
//	memset(FileName, 0, sizeof(FileName));
//	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Player/");
//	strcat_s(FileName, sizeof(FileName), fileName);
//	return FileName;
//	//CreateFromX(FileName);
//	//m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
//	//ownWeight_ = 0.001f;
//}

//
//	@brief	ƒŠƒZƒbƒg
void Bomber::Reset()
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
	bombFlg_ = false;
	invinsibleFlg_ = false;
	bombList_.clear();

	m_Pos = D3DXVECTOR3(-2.25 + charaType_*1.5, 0, -10);
}

////
////	@brief	ˆÚ“®•ûŒü‚ÉƒLƒƒƒ‰ƒNƒ^[‚ª‚¢‚é‚©
////	@note	ˆÚ“®•ûŒü‚ÉƒLƒƒƒ‰ƒNƒ^[‚ª‚¢‚½‚çA‚»‚ÌƒLƒƒƒ‰ƒNƒ^[‚Ìd‚³‚ðŽæ“¾
//void Bomber::MoveCharaHit()
//{
//	float dist = 1;
//	float degree = D3DXToDegree(m_Yaw);
//	CharactorManager* opp = nullptr;
//	for (auto c : aroundCharaList_)
//	{
//		if (collision_->CharaNear(m_Pos, c->m_Pos, dist))
//		{
//			D3DXVECTOR3 vec = c->m_Pos - m_Pos;
//			float angle = (atan2(vec.z, vec.x)*-1) - (D3DX_PI / 2.0f);
//			angle = D3DXToDegree(angle);
//
//			float hitAngle = 90 / 2;
//			if (fabsf(degree - angle) <= hitAngle)
//			{
//				/*opponentWeight_ = c->ownWeight_;*/
//				opponentWeight_ = 0;
//				opp = c;
//			}
//		}
//	}
//	if (opp == nullptr || invinsibleFlg_ == true)
//	{
//		opponentWeight_ = 1;
//	}
//}
//
////
////	@brief			ˆÚ“®ˆ—
////	@param (speed)	ˆÚ“®‘¬“x
//void Bomber::Move(float speed)
//{
//	if (damageFlg_)
//	{
//		damageDrawTime_ = FPS * 0.5;
//		if (damageCount_ >= damageDrawTime_)
//		{
//			damageFlg_ = false;
//			damageCount_ = 0;
//		}
//		return;
//	}
//
//	if (atkNo_ == specialAtk)
//	{
//		knockBackFlg_ = false;
//	}
//
//	if (knockBackFlg_ == true)
//	{
//		KnockBack(knockBackPos_, knockBackDis_, knockBackSpeed_);
//		return;
//	}
//
//	//ƒXƒeƒBƒbƒN‚ÌŒX‚«Žæ“¾
//	D3DXVECTOR3 inputStick;
//	inputStick.x = GamePad::getAnalogValue(charaType_, GamePad::AnalogName::AnalogName_LeftStick_X);
//	inputStick.z = GamePad::getAnalogValue(charaType_, GamePad::AnalogName::AnalogName_LeftStick_Y);
//
//	//‰ñ“]ˆ—
//	const float rotEpsilon = 0.3;
//	if (fabsf(inputStick.x) > rotEpsilon || fabsf(inputStick.z) > rotEpsilon)
//	{
//		Rotation(inputStick);
//	}
//
//
//	//ˆÚ“®
//	const float moveEpsilon = 0.2;	//Œëì–hŽ~—p
//	float sp = 0;
//	if (fabsf(inputStick.x) > moveEpsilon || fabsf(inputStick.z) > moveEpsilon)
//	{
//		if (atkNo_ != specialAtk)
//		{
//			sp = speed;
//		}
//		else
//		{
//			sp = param_->specialMoveSpeed_;
//		}
//
//		if (motionChange_ == true)
//		{
//			if (atkNo_ != specialAtk && motionNo_ != motion_->GetMotion("walk")->id_)
//			{
//				ChangeMotion(motion_, "walk");
//			}
//			else if (atkNo_ == specialAtk && motionNo_ != motion_->GetMotion("specialWalk")->id_)
//			{
//				ChangeMotion(motion_, "specialWalk");
//			}
//			if (atkNo_ == specialAtk)
//			{
//				Sound::getInstance().SE_play("Sh_SPECIAL");
//			}
//		}
//	}
//	else
//	{
//
//		if (motionChange_ == true)
//		{
//			if (atkNo_ != specialAtk && motionNo_ != motion_->GetMotion("wait")->id_)
//			{
//				ChangeMotion(motion_, "wait");
//			}
//		}
//	}
//
//	//opponentWeight_ = 1;
//
//	MoveCharaHit();
//
//
//	m_Dir = D3DXVECTOR3(inputStick.x*sp * opponentWeight_, 0, inputStick.z*sp * opponentWeight_);
//
//	//m_vPos += D3DXVECTOR3(inputStick.x*sp - opponentWeight_, 0, inputStick.z*sp - opponentWeight_);
//
//	GamePad::update();
//
//	//m_Dir = D3DXVECTOR3(m_AxisX.x, m_AxisY.y, m_AxisZ.z);
//	//m_Dir = D3DXVECTOR3(m_Move.x, 0, m_Move.z);
//
//}

//
//	@brief	UŒ‚
void Bomber::Attack()
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
	}
	else if (atkNo_ == charge)
	{
		moveAbleFlg_ = true;
		attackCount_ = 0;
		atkNo_ = specialAtk;
		//invinsibleFlg_ = true;
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = FPS*param_->chargeTime_;
	static bool chargeMotionFlg = false;
	if (0 < attackCount_ && attackCount_ <= inputTime)
	{
		atkNo_ = normalAtk;
	}
	else if (inputTime < attackCount_)
	{
		atkNo_ = charge;
		moveAbleFlg_ = false;
		if (!chargeMotionFlg && motionNo_ != motion_->GetMotion("charge1")->id_)
		{
			motionChange_ = false;
			chargeMotionFlg = true;
			//motionNo_ = motion_->GetMotion("charge")->id_;
			//m_pD3dxMesh->ChangeAnimSet(motionNo_);
			//timeEnd_ = motion_->GetMotion("attack")->frame_;
			//motionSpeed_ = 1 / (float)timeEnd_;
			//motionCount_ = 0;
			ChangeMotion(motion_, "charge1");
		}
		else if (++motionCount_>motionFrame_ && chargeMotionFlg &&  motionNo_ != motion_->GetMotion("charge2")->id_)
		{
			ChangeMotion(motion_, "charge2");
		}
	}

	if (atkNo_ == specialAtk)
	{
		chargeMotionFlg = false;
		Special_Attack();
	}

	/*if (invinsibleFlg_)
	{
		int invincibleTime = param_->specialAttackTime_;
		if (++invisibleCount_ % (FPS * invincibleTime) == 0)
		{
			invinsibleFlg_ = false;
			invisibleCount_ = 0;
		}
	}*/
}

//
//	@brief	’ÊíUŒ‚
void Bomber::Normal_Attack()
{
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("attack")->id_)
	{
		motionChange_ = false;
		//motionNo_ = motion_->GetMotion("attack")->id_;
		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//timeEnd_ = motion_->GetMotion("attack")->frame_;
		//motionSpeed_ = 1 / (float)timeEnd_;
		//motionCount_ = 0;
		ChangeMotion(motion_, "attack");
	}

	InstanceWeapon();


	//atkNo_ = noAtk;
}

//
//	@brief	“ÁŽêUŒ‚
void Bomber::Special_Attack()
{
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("special")->id_)
	{
		motionChange_ = false;
		/*motionNo_ = motion_->GetMotion("special")->id_;
		m_pD3dxMesh->ChangeAnimSet(motionNo_);
		timeEnd_ = motion_->GetMotion("special")->frame_;
		motionSpeed_ = 1 / (float)timeEnd_;
		motionCount_ = 0;*/
		ChangeMotion(motion_, "special");
	}

	InstanceWeapon();

	/*if (++motionCount_%motionFrame_ == 0)
	{
		atkNo_ = noAtk;
		motionChange_ = true;
		moveAbleFlg_ = true;
	}
*/
	/*int invincibleTime = param_->specialAttackTime_;
	if (++motionCount_ % (FPS * invincibleTime) == 0)
	{
		invincibleFlg_ = false;
		motionCount_ = 0;
	}
	atkNo_ = noAtk;*/
}

//
//	@brief	”š’e‚Ì¶¬
void Bomber::InstanceWeapon()
{
	size_t size = param_->chainWeapon_;
	float range = param_->weaponHitReach_;
	float kDist = param_->knockbackDist_;
	float kSpeed = param_->knockbackSpeed_;
	moveAbleFlg_ = false;
	if (++motionCount_>motionFrame_ )
	{
		Sound::getInstance().SE_play("B_SPECIAL");
		motionChange_ = true;
		if (bombList_.empty() || bombList_.size() < size)
		{
			WeaponBall* bomb = new WeaponBall;
			bomb->SetStartPos(m_Pos);
			bomb->SetScale(param_->weaponScale_);
			bomb->SetAttack(param_->normalAtk_);
			bomb->SetDamageList(allCharaList_, charaType_);
			bomb->SetKnockBack(range, kDist, kSpeed, charaType_);
			bomb->SetHitSound("B_DAMAGE_HIT");
			bombList_.push_back(bomb);
		}
		atkNo_ = noAtk;
		moveAbleFlg_ = true;
	}
}

//
//	@brief	”š’e‚ÌXV
void Bomber::WeaponUpdate()
{
	if (!bombList_.empty())
	{
		bombFlg_ = true;
		float delTime = FPS*param_->weaponDelTime_;
		for (auto b : bombList_)
		{
			b->Time_Del_Weapon(delTime);
			b->SetDamageList(allCharaList_, charaType_);
		}
		if (/*b != nullptr &&*/ bombList_[0]->GetDelFlg())
		{
			bombList_.erase(bombList_.begin());
			Sound::getInstance().SE_play("B_NORMALATK");
		}
		if (bombList_.empty())
		{
			bombList_.clear();
			bombFlg_ = false;
		}
	}
}

////
////	@brief	”š’eŽm—pˆÚ“®ˆ—
//void Bomber::Move_Update()
//{
//	float kSpeed = param_->knockbackSpeed_;
//	if (aliveFlg_ == true)
//	{
//		if (knockBackFlg_ == false && moveAbleFlg_==true)
//		{
//			m_Pos += m_Dir;
//		}
//		else if (knockBackFlg_ == true && invinsibleFlg_ == false)
//		{
//			KnockBack(knockBackPos_, knockBackDis_, kSpeed);
//		}
//	}
//}


////
////	@brief			ƒ_ƒ[ƒWŒvŽZ
////	@param (atk)	UŒ‚ŽÒ‚ÌUŒ‚—Í
//void Bomber::DamageCalc(unsigned int atk)
//{
//	if (!(damageFlg_ && invinsibleFlg_))
//	{
//		damageFlg_ = true;
//		Sound::getInstance().SE_play("B_DAMAGE");
//		float damage = 0;
//		//if (invinsibleFlg_ == false)
//		//{
//			damage = atk / (1 + ((float)param_->def_ / 100));
//		//}
//
//		hp_ -= damage;
//		if (hp_ <= 0 || param_->hp_ < hp_)
//		{
//			hp_ = 0;
//			aliveFlg_ = false;
//			damageFlg_ = false;
//		}
//	}
//}


//
//	@brief	Ž€–S‰¹Ä¶
void Bomber::DeadSound()
{
	Sound::getInstance().SE_play("B_DEAD");
}

//
//	@brief	•`‰æ
void Bomber::CharaRender()
{
	/*D3DXVECTOR2 pos(0, 0);
	D3DXVECTOR2 size(1, 1);
	bom_UI["BOM_UI"]->Render(pos,size);*/
	//ƒ‚ƒfƒ‹‚Ì•`‰æ
	mesh_->m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);
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
	//”š’e‚Ì•`‰æ
	if (!bombList_.empty())
	{
		for (auto b : bombList_)
		{
			if (b != nullptr)
			{
				//b->Render();
				bomb_->Render(b->GetPosition(), D3DXVECTOR3(0, 0, 0), b->GetScale());
			}
		}
	}


	//UI•`‰æ
	UIRender();
}