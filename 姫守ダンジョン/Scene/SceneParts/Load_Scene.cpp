#include "Load_Scene.h"

Load_Scene::Load_Scene()
{
	loading_UI = new D3D11_SPRITE;
	debugText_ = new D3D11_TEXT;
}

Load_Scene::~Load_Scene()
{
	delete loading_UI;
	loading_UI = nullptr;
}

void Load_Scene::Init()
{
	//loading_UI->Init(L"./UI/UI_Tex/lord.png", /*0, */D3DXVECTOR2(0, 0), D3DXVECTOR2(16369, 255), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	//loading_UI->Init(D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), true, L"./UI/UI_Tex/lord.png", D3DXVECTOR2(8, 2), 3);
	loading_UI->Init(L"./UI/UI_Tex/lord.png", D3DXVECTOR2(13, 1), 10);
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

	D3DXVECTOR3 pos(10, 11, -23);
	D3DXVECTOR2 scale(0.1, 0.05);
	D3DXVECTOR3 rot(0.128,D3DX_PI,0);
	float speed = 0.001;
	rot.x += -(GetKeyState(VK_LEFT) & 0x80)*speed + (GetKeyState(VK_RIGHT) & 0x80)*speed;
	loading_UI->Render(pos, scale, rot);

	char str[256];
	sprintf(str, "rot.x:%f", rot.x);
	debugText_->Render(str, 0, 50);
}
