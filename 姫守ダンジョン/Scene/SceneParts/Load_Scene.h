#pragma once
#include <iostream>
#include <string>
#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"
#include "./Title_Scene.h"
#include "./CharactorSelection_Scene.h"
#include "./Main_Scene.h"
#include "./../../Camera.h"
#include "./../../UI/D3D11_SPRITE.h"

#define LOADUI_SPRITE 13
class Load_Scene :public Scene
{
private:
	D3D11_SPRITE* loading_UI;
	//TD_Graphics* loadingUI_[LOADUI_SPRITE];
	TD_Graphics* descriptionUI_;
	D3D11_TEXT* debugText_;
	Camera* camera_;

	int uiAnimCount_;
public:
	Load_Scene();
	virtual ~Load_Scene();

	void Init();
	SceneBase* Update(SceneRoot* root);
	void Render();
	void Destroy();
};