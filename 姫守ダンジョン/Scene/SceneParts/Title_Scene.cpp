#include "./Title_Scene.h"

Title_Scene::Title_Scene()
{
	title_UI["TITLE_UI"] = new TD_Graphics;
	title_UI["PUSH_A"] = new TD_Graphics;
	camera_ = new Camera;
	creator_ = new CharactorCreator;
}

Title_Scene::~Title_Scene()
{
	delete title_UI["TITLE_UI"];
	title_UI["TITLE_UI"] = nullptr;
	delete title_UI["PUSH_A"];
	title_UI["PUSH_A"] = nullptr;
	delete camera_;
	camera_ = nullptr;
	delete creator_;
	creator_ = nullptr;

}

void Title_Scene::Init()
{
	camera_->gazePoint_ = D3DXVECTOR3(0, 3, 0);
	camera_->movePow_ = D3DXVECTOR3(0, 8, -20);
	mesh_sword_ = creator_->LoadChara("åïém");
	mesh_shiled_ = creator_->LoadChara("èÇém");
	mesh_bomber_ = creator_->LoadChara("îöíeém");
	mesh_witch_ = creator_->LoadChara("ñÇì±ém");
	mesh_princess_ = creator_->LoadChara("ïP");
	mesh_slime_ = creator_->LoadChara("ÉXÉâÉCÉÄ");
	mesh_goblin_ = creator_->LoadChara("ÉSÉuÉäÉì");
	mesh_skelton_ = creator_->LoadChara("ÉXÉPÉãÉgÉì");
	mesh_stage_ = creator_->LoadStage("É^ÉCÉgÉã");
	//while (i < enemyMax)
	float dist = 10;
	for (int i = 0; i < enemyMax; i++)
	{
		while (1)
		{
			enemyPos_[i] = D3DXVECTOR3(rand() % enemyInsRange - enemyInsRange/2, 0, rand() % enemyInsRange- enemyInsRange/2);
			if (enemyPos_[i].x < -dist || dist < enemyPos_[i].x
				||enemyPos_[i].z < -dist || dist < enemyPos_[i].z)
			{
				break;
			}
		}

		D3DXVECTOR3 pos = D3DXVECTOR3(0 - enemyPos_[i].x, 0, 0 - enemyPos_[i].z);
		enemyRot_[i] = (atan2(pos.z, pos.x)*-1) - (D3DX_PI / 2.0f);
		/*if ((enemyPos_[i].x < -5 || enemyPos_[i].x>5 )&& (enemyPos_[i].z<-5 && enemyPos_[i].z > 5))
		{
			++i;
		}*/
	}

	/*Effect::getInstance().Effect_Play(name, D3DXVECTOR3(0, 0, 0));
	Effect::getInstance().SetScale(name, 0.5);*/
	title_UI["TITLE_UI"]->Init(L"./UI/UI_Tex/title.png", /*0, */D3DXVECTOR2(0, 0), D3DXVECTOR2(6180, 1529), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	title_UI["PUSH_A"]->Init(L"./UI/UI_Tex/start_button.png", /*0, */D3DXVECTOR2(0, 0), D3DXVECTOR2(1299, 264), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	Sound::getInstance().BGM_play("TITLE");
	alfa_ = 0;
}

void Title_Scene::Destroy()
{
	Sound::getInstance().BGM_stop("TITLE");
	SAFE_DELETE(mesh_sword_);
	SAFE_DELETE(mesh_shiled_);
	SAFE_DELETE(mesh_bomber_);
	SAFE_DELETE(mesh_witch_);
	SAFE_DELETE(mesh_princess_);
	SAFE_DELETE(mesh_slime_);
	SAFE_DELETE(mesh_goblin_);
	SAFE_DELETE(mesh_skelton_);
	//SAFE_DELETE(mesh_stage_);
}

SceneBase* Title_Scene::Update(SceneRoot* root)
{
	camera_->TitleUpdate(20);

	SceneBase* next = this;

	static bool nextFlg = false;
	for (int i = 0; i < 4; i++)
	{
		if (GamePad::checkInput(i, GamePad::InputName::A)||GetKeyState(VK_SPACE)&0x80)
		{
			nextFlg = true;
			Sound::getInstance().SE_play("DECISION_SE");
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
	D3DXVECTOR2 size(0.2, 0.25);
	/*if (alfa_ < 1.0f)
	{
		title_UI["TITLE_UI"]->SetAlfa(alfa_);
		alfa_ += 0.01f;
	}*/
	title_UI["TITLE_UI"]->Render(pos, size, true);
	title_UI["PUSH_A"]->Render(D3DXVECTOR2(610, 880), D3DXVECTOR2(0.5, 0.5), true);

	float scale = 0.5;
	float dist = 5;
	float speed = 1.0f / 40.0f;
	mesh_sword_->Render(D3DXVECTOR3(0, 0, -dist), 0, D3DXVECTOR3(scale, scale, scale), camera_->movePow_);
	mesh_sword_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_shiled_->Render(D3DXVECTOR3(dist, 0, 0), D3DXToRadian(-90), D3DXVECTOR3(scale, scale, scale));
	mesh_shiled_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_bomber_->Render(D3DXVECTOR3(0, 0, dist), D3DXToRadian(180), D3DXVECTOR3(scale, scale, scale));
	mesh_bomber_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_witch_->Render(D3DXVECTOR3(-dist, 0, 0), D3DXToRadian(90), D3DXVECTOR3(scale, scale, scale));
	mesh_witch_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_princess_->Render(D3DXVECTOR3(0, 0, 0), D3DXToRadian(-45), D3DXVECTOR3(scale, scale, scale));
	mesh_princess_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);

	//ÉXÉeÅ[ÉWÇÃï`âÊ
	mesh_stage_->Render(D3DXVECTOR3(0, 0.8, 0), D3DXVECTOR3(0, 0, 0), 2);
	////mesh_slime_->Render(D3DXVECTOR3(0, 0, 8), 0, D3DXVECTOR3(0.5, 0.5, 0.5));
	int enemyCount = 0;
	for (int i = 0; i < oneEnemyMax; i++)
	{
		mesh_slime_->Render(enemyPos_[enemyCount], enemyRot_[enemyCount], D3DXVECTOR3(scale, scale, scale));
		++enemyCount;
	}
	for (int i=0; i < oneEnemyMax; i++)
	{
		mesh_goblin_->Render(enemyPos_[enemyCount], enemyRot_[enemyCount], D3DXVECTOR3(scale, scale, scale));
		++enemyCount;
	}
	for (int i=0; i < oneEnemyMax; i++)
	{
		mesh_skelton_->Render(enemyPos_[enemyCount], enemyRot_[enemyCount], D3DXVECTOR3(scale, scale, scale));
		++enemyCount;
	}
	mesh_slime_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_goblin_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_skelton_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	camera_->Render();
}


void Title_Scene::DebugSetJob()
{
	strcpy(CharactorCreator::player1_, "åïém");
	strcpy(CharactorCreator::player2_, "èÇém");
	strcpy(CharactorCreator::player3_, "îöíeém");
	strcpy(CharactorCreator::player4_, "ñÇì±ém");
}