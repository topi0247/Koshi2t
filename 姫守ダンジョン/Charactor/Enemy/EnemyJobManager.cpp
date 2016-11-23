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
	targetChar_->DamageCalc(param_->atk_);
	targetChar_->KnockBack(m_Pos,dist);
}