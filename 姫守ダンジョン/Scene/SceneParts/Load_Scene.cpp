#include "Load_Scene.h"

Load_Scene::Load_Scene()
{
	loading_UI = new D3D11_SPRITE;
	descriptionUI_ = new TD_Graphics;
	debugText_ = new D3D11_TEXT;
	camera_ = new Camera;
}

Load_Scene::~Load_Scene()
{
	delete loading_UI;
	loading_UI = nullptr;
	delete descriptionUI_;
	descriptionUI_ = nullptr;
	delete camera_;
	camera_ = nullptr;
}

void Load_Scene::Init()
{
	loading_UI->Init(L"./UI/UI_Tex/lord.png", D3DXVECTOR2(13, 1), 10);
	descriptionUI_->Init(L"./UI/UI_Tex/loadscene.png", D3DXVECTOR2(WINDOW_WIDTH, WINDOW_HEIGHT), D3DXVECTOR4(1,1,1,1),GrapRect(0,1,0,1));
	camera_->movePow_ = D3DXVECTOR3(-7.2, 8.5, -42);
	uiAnimCount_ = 0;
	camera_->gazePoint_ = camera_->movePow_;
	camera_->gazePoint_.z = camera_->movePow_.z + 10;
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

	static D3DXVECTOR3 pos(0, 0, 0);
	D3DXVECTOR2 scale(0.1, 0.02);
	D3DXVECTOR3 rot(0,D3DX_PI,0);
	loading_UI->Render(pos, scale, rot);

	descriptionUI_->Render(D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1), false);
	camera_->Render();

#ifdef _DEBUG
	char str[256];
	sprintf(str, "pos.x:%f pos.y:%f pos.z:%f", camera_->movePow_.x, camera_->movePow_.y, camera_->movePow_.z);
	debugText_->Render(str, 0, 50);
#endif // _DEBUG


}
