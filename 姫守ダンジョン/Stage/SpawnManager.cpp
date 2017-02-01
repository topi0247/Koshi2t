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
	//delete spawnGate_;
	//spawnGate_ = nullptr;

	SAFE_DELETE(spawnMesh_);
	spawnList_.clear();
	spawnList_.shrink_to_fit();
}

//
//	@brief	初期化
void SpawnManager::Init(char* name)
{
	spawnMesh_ = creator_->LoadStage(name);
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

	uiDrawFlg_ = false;
	seal_UI->Init(L"./UI/UI_Tex/success_font.png", /*0, */D3DXVECTOR2(0, 0), D3DXVECTOR2(1920, 1080), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
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
		//functionList_.push_back(temp);
		//renderList_.push_back(temp);
	}

	/*	要修正の必要あり　*/
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
			//Effect::getInstance().Update("spwner", D3DXVECTOR3(s->GetPos().x, 0, s->GetPos().z));
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
		/*-要修正------------------------------------------------*/
		if (sealSpawn_->GetSpawnGateAttr()->id_ == 0)
		{
			Effect::getInstance().Effect_Stop("spwner1");
		}
		else if (sealSpawn_->GetSpawnGateAttr()->id_ == 1)
		{
			Effect::getInstance().Effect_Stop("spwner2");
		}
		/*-----------------------------------------------------*/
		uiDrawFlg_ = true;
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

	//uiDrawFlg_ = true;
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