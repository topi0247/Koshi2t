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
}

//=======ƒXƒ‰ƒCƒ€=======//
//Slim::Slim()
//{
//}

void Slim::NormalAttack()
{
}