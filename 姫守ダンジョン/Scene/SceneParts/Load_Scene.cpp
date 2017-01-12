#include "Load_Scene.h"

Load_Scene::Load_Scene()
{
	loading_UI = new TD_Graphics;
}

Load_Scene::~Load_Scene()
{
	delete loading_UI;
	loading_UI = nullptr;
}

void Load_Scene::Init()
{
	loading_UI->Init(L"./UI/UI_Tex/lord.png", /*0, */D3DXVECTOR2(0, 0), D3DXVECTOR2(16369, 255), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
}

void Load_Scene::Destroy()
{

}

SceneBase* Load_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;

	return next;
}

void Load_Scene::Render()
{
	D3DXVECTOR2 pos(0, 0);
	D3DXVECTOR2 scale(1, 1);
	loading_UI->AnimRender(pos, scale, true,1);
}
