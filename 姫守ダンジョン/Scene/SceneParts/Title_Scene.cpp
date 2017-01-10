#include "./Title_Scene.h"

Title_Scene::Title_Scene()
{
	title_UI["TITLE_UI"] = new TD_Graphics;
}

Title_Scene::~Title_Scene()
{
	delete title_UI["TITLE_UI"];
}
std::string name = "beam2";
void Title_Scene::Init()
{
	camera_ = new Camera;
	camera_->gazePoint_ = D3DXVECTOR3(0, 3, 0);
	camera_->movePow_ = D3DXVECTOR3(0, 7, -25);
	CharactorCreator* creator = new CharactorCreator;
	mesh_sword_ = creator->GetCharaModel("Œ•Žm");
	mesh_shiled_ = creator->GetCharaModel("‚Žm");
	mesh_bomber_ = creator->GetCharaModel("”š’eŽm");
	mesh_witch_ = creator->GetCharaModel("–‚“±Žm");
	mesh_princess_ = creator->GetCharaModel("•P");
	mesh_enemy_ = creator->GetCharaModel("ƒXƒ‰ƒCƒ€");


	/*Effect::getInstance().Effect_Play(name, D3DXVECTOR3(0, 0, 0));
	Effect::getInstance().SetScale(name, 0.5);*/
	title_UI["TITLE_UI"]->Init(L"./UI/UI_Tex/title.png", /*0, */D3DXVECTOR2(0, 0), D3DXVECTOR2(1920, 1080), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
}

void Title_Scene::Destroy()
{
	delete camera_;
}


SceneBase* Title_Scene::Update(SceneRoot* root)
{
	camera_->TitleUpdate(25);

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

	return next;
}

void Title_Scene::Render()
{
	D3DXVECTOR2 pos(0, 0);
	D3DXVECTOR2 size(1, 1);
	title_UI["TITLE_UI"]->Render(pos, size,true);

	float scale = 0.5;
	float dist = 5;
	float speed = 1.0f / 40.0f;
	mesh_sword_->Render(D3DXVECTOR3(0, 0, -dist), 0, D3DXVECTOR3(scale, scale, scale));
	mesh_sword_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_shiled_->Render(D3DXVECTOR3(dist, 0, 0), D3DXToRadian(-90), D3DXVECTOR3(scale, scale, scale));
	mesh_shiled_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_bomber_->Render(D3DXVECTOR3(0, 0, dist), D3DXToRadian(180), D3DXVECTOR3(scale, scale, scale));
	mesh_bomber_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_witch_->Render(D3DXVECTOR3(-dist, 0, 0), D3DXToRadian(90), D3DXVECTOR3(scale, scale, scale));
	mesh_witch_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	mesh_princess_->Render(D3DXVECTOR3(0, 0, 0), 0, D3DXVECTOR3(scale, scale, scale));
	mesh_princess_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);

	//Effect::getInstance().Update(name, D3DXVECTOR3(0, 0, 0));
	//Effect::getInstance().Draw();

	camera_->Render();
}