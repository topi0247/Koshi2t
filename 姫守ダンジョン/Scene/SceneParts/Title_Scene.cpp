#include "./Title_Scene.h"


Title_Scene::Title_Scene()
{
	title_UI["TITLE_UI"] = new TD_Graphics;
}

Title_Scene::~Title_Scene()
{
	delete title_UI["TITLE_UI"];
}

void Title_Scene::Init()
{
	title_UI["TITLE_UI"]->Init(L"./UI/UI_Tex/title_UI.png", 0, D3DXVECTOR2(0, 0), D3DXVECTOR2(1920, 1080), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
}

void Title_Scene::Destroy()
{
}

SceneBase* Title_Scene::Update(SceneRoot* root)
{

	SceneBase* next = this;

	//if (GetKeyState(VK_F1) & 0x80)
	if (GamePad::checkInput(0, GamePad::InputName::A))
	{
		next = new CharactorSelection_Scene;
	}

	GamePad::update();

	return next;
}

void Title_Scene::Render()
{
	title_UI["TITLE_UI"]->Render(0, 0, 0, 0);
}