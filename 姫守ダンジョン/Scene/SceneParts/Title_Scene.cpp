#include "./Title_Scene.h"

Title_Scene::Title_Scene()
{
	title_UI["TITLE_UI"] = new TD_Graphics;
	camera_ = new Camera;
	creator_ = new CharactorCreator;
}

Title_Scene::~Title_Scene()
{
	delete title_UI["TITLE_UI"];
	title_UI["TITLE_UI"] = nullptr;
	delete camera_;
	camera_ = nullptr;
	delete creator_;
	creator_ = nullptr;
	
}

void Title_Scene::Init()
{
	camera_->gazePoint_ = D3DXVECTOR3(0, 3, 0);
	camera_->movePow_ = D3DXVECTOR3(0, 8, -20);
	mesh_sword_ = creator_->LoadChara("Œ•m");
	mesh_shiled_ = creator_->LoadChara("‚m");
	mesh_bomber_ = creator_->LoadChara("”š’em");
	mesh_witch_ = creator_->LoadChara("–‚“±m");
	mesh_princess_ = creator_->LoadChara("•P");
	mesh_enemy_ = creator_->LoadChara("ƒXƒ‰ƒCƒ€");
	mesh_stage_ = creator_->LoadStage("ƒ^ƒCƒgƒ‹");

	int i = 0;
	//while (i < enemyMax)
	for(int i=0;i<enemyMax;i++)
	{
		enemyPos_[i] = D3DXVECTOR3(rand() % 20 - 10, 0, rand() % 20 - 10);
		/*if ((enemyPos_[i].x < -5 || enemyPos_[i].x>5 )&& (enemyPos_[i].z<-5 && enemyPos_[i].z > 5))
		{
			++i;
		}*/
	}

	/*Effect::getInstance().Effect_Play(name, D3DXVECTOR3(0, 0, 0));
	Effect::getInstance().SetScale(name, 0.5);*/
	title_UI["TITLE_UI"]->Init(L"./UI/UI_Tex/title.png", /*0, */D3DXVECTOR2(0, 0), D3DXVECTOR2(1920, 1080), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
}

void Title_Scene::Destroy()
{
	SAFE_DELETE(mesh_sword_);
	SAFE_DELETE(mesh_shiled_);
	SAFE_DELETE(mesh_bomber_);
	SAFE_DELETE(mesh_witch_);
	SAFE_DELETE(mesh_princess_);
	SAFE_DELETE(mesh_enemy_);
	//SAFE_DELETE(mesh_stage_);
}

SceneBase* Title_Scene::Update(SceneRoot* root)
{
	camera_->TitleUpdate(20);

	SceneBase* next = this;

	static bool nextFlg = false;
	for (int i = 0; i < 4; i++)
	{
		if (GamePad::checkInput(i, GamePad::InputName::A))
		{
			nextFlg = true;
		}
	}
	if (nextFlg)
	{
		next = new CharactorSelection_Scene;
		nextFlg = false;
	}

	GamePad::update();

#ifdef _DEBUG
	//if (GetKeyState(VK_SPACE))
	//{
	//	//DebugSetJob();
	//	//next = new Main_Scene;
	//	next = new Load_Scene;
	//}
#endif //_DEBUG

	return next;
}

void Title_Scene::Render()
{
	D3DXVECTOR2 pos(350, 0);
	D3DXVECTOR2 size(0.6, 0.4);
	title_UI["TITLE_UI"]->Render(pos, size, true);

	float scale = 0.5;
	float dist = 5;
	float speed = 1.0f / 40.0f;
	mesh_sword_->Render(D3DXVECTOR3(0, 0, -dist), 0, D3DXVECTOR3(scale, scale, scale), camera_->movePow_);
	mesh_sword_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_shiled_->Render(D3DXVECTOR3(dist, 0, 0), D3DXToRadian(-90), D3DXVECTOR3(scale, scale, scale), camera_->movePow_);
	mesh_shiled_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_bomber_->Render(D3DXVECTOR3(0, 0, dist), D3DXToRadian(180), D3DXVECTOR3(scale, scale, scale), camera_->movePow_);
	mesh_bomber_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_witch_->Render(D3DXVECTOR3(-dist, 0, 0), D3DXToRadian(90), D3DXVECTOR3(scale, scale, scale), camera_->movePow_);
	mesh_witch_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_princess_->Render(D3DXVECTOR3(0, 0, 0), D3DXToRadian(-45), D3DXVECTOR3(scale, scale, scale), camera_->movePow_);
	mesh_princess_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);

	//ƒXƒe[ƒW‚Ì•`‰æ
	mesh_stage_->Render(D3DXVECTOR3(0, 0.8, 0), D3DXVECTOR3(0, 0, 0), 2);
	////mesh_enemy_->Render(D3DXVECTOR3(0, 0, 8), 0, D3DXVECTOR3(0.5, 0.5, 0.5));
	for (int i = 0; i < enemyMax; i++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(0 - enemyPos_[i].x, 0, 0 - enemyPos_[i].z);
		float angel = (atan2(pos.z, pos.x)*-1) - (D3DX_PI / 2.0f);
		mesh_enemy_->Render(enemyPos_[i], angel, D3DXVECTOR3(scale, scale, scale));
	}
	mesh_enemy_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);

	//Effect::getInstance().Update(name, D3DXVECTOR3(0, 0, 0));
	//Effect::getInstance().Draw();

	camera_->Render();
}


void Title_Scene::DebugSetJob()
{
	strcpy(CharactorCreator::player1_, "Œ•m");
	strcpy(CharactorCreator::player2_, "‚m");
	strcpy(CharactorCreator::player3_, "”š’em");
	strcpy(CharactorCreator::player4_, "–‚“±m");
}