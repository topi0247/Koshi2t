#include "./CharactorSelection_Scene.h"

CharactorSelection_Scene::CharactorSelection_Scene()
{
	charaSelect_UI["CHARASELECT_UI"] = new TD_Graphics;
	charaSelect_UI["FINGER_UI"] = new TD_Graphics;
}

CharactorSelection_Scene::~CharactorSelection_Scene()
{
	delete charaSelect_UI["CHARASELECT_UI"];
	delete charaSelect_UI["FINGER_UI"];
}

void CharactorSelection_Scene::Init()
{
	charaSelect_UI["CHARASELECT_UI"]->Init(L"./UI/UI_Tex/character_select.png", 0, D3DXVECTOR2(0, 0), D3DXVECTOR2(1920, 1080), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["FINGER_UI"]->Init(L"./UI/UI_Tex/finger.png", 0, D3DXVECTOR2(0, 0), D3DXVECTOR2(230, 300), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
}

void CharactorSelection_Scene::Destroy()
{

}

SceneBase* CharactorSelection_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;

	if (GamePad::checkInput(0, GamePad::InputName::START))
	{
		next = new Main_Scene;
	}

	if (GamePad::checkInput(0, GamePad::InputName::B))
	{
		next = new Title_Scene;
	}


	GamePad::update();
	return next;
}

void CharactorSelection_Scene::Render()
{
	charaSelect_UI["CHARASELECT_UI"]->Render(0, 0, 0, 0);
	charaSelect_UI["FINGER_UI"]->Render(0, 0, 0, 0);
}