//
//	@file	JobManager.h
//	@brief	“G‚²‚Æ‚Ìˆ—
//	@date	2016/11/13
//	@outher	‹g‰z‘å‹R


#include "EnemyJobManager.h"

EnemyJobManager::EnemyJobManager()
{
}

EnemyJobManager::~EnemyJobManager()
{
}

void EnemyJobManager::CharaUpdate()
{
	m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);

	float speed = param_->moveSpeed_;
	MoveCharaHit();
	Move(speed);

	Attack();
}

//=======ƒXƒ‰ƒCƒ€=======//
//Slim::Slim()
//{
//}

void Slim::NormalAttack()
{
	float dist = 3;
	float speed = 1;
	targetChar_->DamageCalc(param_->atk_);
	targetChar_->KnockBack(m_Pos,dist,speed);
}

//=======ƒSƒuƒŠƒ“========//
void Goblin::NormalAttack()
{
	float dist = 3;
	float speed = 1;
	targetChar_->DamageCalc(param_->atk_);
	targetChar_->KnockBack(m_Pos, dist, speed);
}

//=======ƒXƒPƒ‹ƒgƒ“======//
void Skeleton::NormalAttack()
{
	float dist = 1;
	float speed = 1;
	WeaponBall* atkBall=new WeaponBall();
	D3DXVECTOR3 vec(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);
	atkBall->SetDir(vec);
	atkBall->SetDamageList(allCharaList_, charaType_);
	atkBall->SetKnockBack(dist, param_->attackReach_,speed);
	atkBall->SetAttack(param_->atk_);
	atkList_.push_back(atkBall);
}


void Skeleton::CharaRender()
{
	Render(m_Pos);

	if (!atkList_.empty())
	{
		for (auto a : atkList_)
		{
			//a->Render();
		}
	}
}