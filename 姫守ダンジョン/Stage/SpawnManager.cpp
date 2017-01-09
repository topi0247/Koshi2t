//
//	@file	SpawnManager.cpp
//	@brief	スポーンゲート管理クラス
//	@date	2016/11/28
//	@author	仁科香苗

#include "./SpawnManager.h"

//
//	@brief	コンストラクタ
SpawnManager::SpawnManager()
{
	spawnGateRead_ = new SpawnGateRead;
}

//
//	@brief	デストラクタ
SpawnManager::~SpawnManager()
{
	delete spawnGateRead_;
	spawnGateRead_ = nullptr;
	//delete spawnGate_;
	//spawnGate_ = nullptr;

	SAFE_DELETE(spawnMesh_);
	spawnList_.clear();
}

//
//	@brief	初期化
void SpawnManager::Init(char* name)
{
	CharactorCreator* creator = new CharactorCreator;
	spawnMesh_ = creator->GetStageModel(name);
	//delete creator;
	//creator = nullptr;
	SpawnSet();
	/*spawnMesh_ = new CD3DXMESH;

	char FileName[80];
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Stage/");
	strcat_s(FileName, sizeof(FileName), name);
	if (FAILED(spawnMesh_->LoadXMesh(FileName)))
	{
		return;
	}

	SpawnSet();*/
}

//
//	@brief	スポーンゲートの準備
void SpawnManager::SpawnSet()
{
	spawnGateRead_->SpawnGate_Read();
	spawnGate_ = spawnGateRead_->GetSpawnGate("stage5");
	std::vector<SpawnGateAttr*> tempAttr = spawnGate_->GetStageAllSpawnGate();
	for (int i = 0; i < spawnGate_->GetCount(); i++)
	{
		Spawn* temp = new Spawn;
		temp->SpawnInit(tempAttr[i]);
		spawnList_.push_back(temp);
		//functionList_.push_back(temp);
		//renderList_.push_back(temp);
	}
}

//
//	@brief	リセット
void SpawnManager::Reset()
{
	timeCount_ = 0;
	spawnList_.clear();
	functionList_.clear();
	renderList_.clear();
	sealSpawn_ = nullptr;


	spawnGateRead_->SpawnGate_Read();
	spawnGate_ = spawnGateRead_->GetSpawnGate("stage5");
	std::vector<SpawnGateAttr*> tempAttr = spawnGate_->GetStageAllSpawnGate();
	for (int i = 0; i < spawnGate_->GetCount(); i++)
	{
		Spawn* temp = new Spawn;
		temp->SpawnInit(tempAttr[i]);
		spawnList_.push_back(temp);
		//functionList_.push_back(temp);
		//renderList_.push_back(temp);
	}
}

//
//	@brief	更新処理
void SpawnManager::Update(/*ParameterRead* param, */CharactorManager* target)
{
	if (!spawnList_.empty())
	{
		for (auto s : spawnList_)
		{
			s->ListSet(target);
		}
	}
}

//
//	@brief	エネミーのスポーン
std::vector<EnemyJobManager*> SpawnManager::OutEnemy()
{
	std::vector<EnemyJobManager*> tempPush;
	if (!spawnList_.empty())
	{
		for (auto f : spawnList_)
		{
			if (!f->EnemySpawn().empty())
			{
				std::vector<EnemyJobManager*> temp = f->EnemySpawn();
				for (auto e : temp)
				{
					tempPush.push_back(e);
				}
				f->ListReset();
			}
		}
	}

	return tempPush;
}

//
//	@brief	スポーンの封印
void SpawnManager::SealSpawn(Spawn* spawn)
{
	sealSpawn_ = spawn;

	if (sealSpawn_ != nullptr)
	{
		auto elS = std::find(spawnList_.begin(), spawnList_.end(), sealSpawn_);
		//auto elF = std::find(functionList_.begin(), functionList_.end(), sealSpawn_);
		//auto elR = std::find(renderList_.begin(), renderList_.end(), sealSpawn_);

		delete(*elS);
		spawnList_.erase(elS);
		//functionList_.erase(elF);
		//renderList_.erase(elR);
	}
}

//
//	@brief	描画
void SpawnManager::Render()
{
	if (!spawnList_.empty())
	{
		for (auto s : spawnList_)
		{
			spawnMesh_->Render(s->GetPos(), s->GetRot(), s->GetScale());
		}
	}
}