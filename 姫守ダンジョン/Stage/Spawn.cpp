//
//	@file	Spawn.cpp
//	@brief	スポーンゲートクラス
//	@date	2016/11/25
//	@author	仁科香苗

#include "./Spawn.h"

//
//	@brief	コンストラクタ
Spawn::Spawn()
	:timeCount_(0)
{
	enemyMesh_ = new CD3DXSKINMESH;
	creator_ = new CharactorCreator;
}

//
//	@brief	デストラクタ
Spawn::~Spawn()
{
	delete creator_;
	creator_ = nullptr;
}

//
//	@brief				スポーンゲートの初期化
//	@param(spawnInfo)	スポーンゲートの情報
//	@param(mesh)		スポーンゲートのメッシュ
void Spawn::SpawnInit(SpawnGateAttr* spawnInfo, CD3DXSKINMESH* mesh)
{
	scale_ = 0.5;
	rot_ = D3DXVECTOR3(0, 0, 0);
	spawn_ = spawnInfo;
	enemyMesh_ = creator_->LoadChara(spawn_->enemyName_);
}

//
//	@brief			エネミーリストのセット
//	@param(target)	ターゲットキャラ
void Spawn::ListSet(CharactorManager* target)
{
	srand((unsigned)time(NULL));
	tempCharactor_ = target;
	int spawnTime = FPS*spawn_->interval_;

	if (timeCount_++%spawnTime == 0)
	{
		int width = spawn_->leftBack_.x +spawn_->rightFront_.x;		//幅
		int height = spawn_->leftBack_.z +spawn_->rightFront_.z;	//高さ(z軸)
		D3DXVECTOR3 tempPos = D3DXVECTOR3(spawn_->pos_.x - spawn_->leftBack_.x, 0, spawn_->pos_.z +spawn_->leftBack_.z);	//出現座標の一番左奥
		int amount_ = spawn_->amount_;
		for (int i = 0; i < amount_; i++)
		{
			EnemyJobManager* enemy;
			if (strcmp(spawn_->enemyName_, "スライム") == 0)
			{
				enemy = new Slim;
			}
			else if (strcmp(spawn_->enemyName_, "ゴブリン") == 0)
			{
				enemy = new Goblin;
			}
			else if (strcmp(spawn_->enemyName_, "スケルトン") == 0)
			{
				enemy = new Skeleton;
			}
			enemy->CharaInit(spawn_->enemyName_);
			enemy->SetModel(enemyMesh_);
			enemy->SetTarget(tempCharactor_);
			enemy->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
			enemy->m_Pos = D3DXVECTOR3(rand() % width +tempPos.x, 0, tempPos.z - rand() % height);
			insEnemyList_.push_back(enemy);
		}
	}
}

//
//	@brief	エネミーのスポーン
std::vector<EnemyJobManager*> Spawn::EnemySpawn()
{
	return insEnemyList_;
}

//
//	@brief	エネミーリストのリセット
void Spawn::ListReset()
{
	insEnemyList_.clear();
}