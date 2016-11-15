//
//	@file	JobManager.h
//	@brief	“G‚²‚Æ‚Ìˆ—
//	@date	2016/11/13
//	@outher	‹g‰z‘å‹R


#include "EnemyJobManager.h"

EnemyJobManager::EnemyJobManager()
{
	m_vPos = D3DXVECTOR3(0, -0.05, 0);
}

EnemyJobManager::~EnemyJobManager()
{
}

void EnemyJobManager::CharaUpdate()
{
	Move(0.05);
}

//=======ƒXƒ‰ƒCƒ€=======//
//Slim::Slim()
//{
//}

void Slim::NormalAttack()
{
}