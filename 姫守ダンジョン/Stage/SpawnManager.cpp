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
	seal_UI = new TD_Graphics;
	spawnGateRead_ = new SpawnGateRead;
	creator_ = new CharactorCreator;
}

//
//	@brief	デストラクタ
SpawnManager::~SpawnManager()
{
	delete seal_UI;
	seal_UI = nullptr;

	delete spawnGateRead_;
	spawnGateRead_ = nullptr;

	delete creator_;
	creator_ = nullptr;

	SAFE_DELETE(spawnMesh_);
	spawnList_.clear();
	spawnList_.shrink_to_fit();
}

//
//	@brief			初期化
//	@param(name)	スポーンゲート名
void SpawnManager::Init(char* name)
{
	spawnMesh_ = creator_->LoadStage(name);
	SpawnSet();
	uiDrawFlg_ = false;
	seal_UI->Init(L"./UI/UI_Tex/success_font.png", D3DXVECTOR2(1920, 1080), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
}

//
//	@brief	スポーンゲートの準備
void SpawnManager::SpawnSet()
{
	spawnGateRead_->SpawnGate_Read();
	spawnGate_ = spawnGateRead_->GetSpawnGate("stage5");
	std::vector<SpawnGateAttr*> tempAttr = spawnGate_->GetStageAllSpawnGate();
	EnemyManager::SetBusStop(spawnGate_->GetBusStop());

	for (int i = 0; i < spawnGate_->GetCount(); i++)
	{
		Spawn* temp = new Spawn;
		CD3DXSKINMESH* mesh = creator_->LoadChara(tempAttr[i]->enemyName_);
		temp->SpawnInit(tempAttr[i], mesh);
		spawnList_.push_back(temp);
	}

	Effect::getInstance().Effect_Play("spwner1", tempAttr[0]->pos_);
	Effect::getInstance().Effect_Play("spwner2", tempAttr[1]->pos_);
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
		CD3DXSKINMESH* mesh = creator_->LoadChara(tempAttr[i]->enemyName_);
		temp->SpawnInit(tempAttr[i], mesh);
		spawnList_.push_back(temp);
	}
}

//
//	@brief			更新処理
//	@param(target)	一番最初のターゲットキャラクター
void SpawnManager::Update(CharactorManager* target)
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
		if (sealSpawn_->GetSpawnGateAttr()->id_ == 0)
		{
			Effect::getInstance().Effect_Stop("spwner1");
		}
		else if (sealSpawn_->GetSpawnGateAttr()->id_ == 1)
		{
			Effect::getInstance().Effect_Stop("spwner2");
		}
		uiDrawFlg_ = true;
		auto elS = std::find(spawnList_.begin(), spawnList_.end(), sealSpawn_);
		delete(*elS);
		spawnList_.erase(elS);
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

	if (uiDrawFlg_)
	{
		static int count = 1;
		static D3DXVECTOR2 pos(WINDOW_WIDTH, 10);
		D3DXVECTOR2 size(0.3, 0.2);
		seal_UI->Render(pos, size, true);
		if (pos.x >= WINDOW_WIDTH / 2 || count == 0)
		{
			pos.x -= 100;
			if (pos.x <= -1000)
			{
				uiDrawFlg_ = false;
				count = 1;
				pos = D3DXVECTOR2(WINDOW_WIDTH, 10);
			}
		}
		else if (++count % (FPS * 2) == 0)
		{
			count = 0;
		}
	}
}