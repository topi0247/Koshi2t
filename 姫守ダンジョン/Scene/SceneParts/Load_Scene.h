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

class Load_Scene :public Scene
{
private:
	D3D11_SPRITE* loading_UI;
	D3D11_TEXT* debugText_;
	Camera* camera_;
public:
	Load_Scene();
	virtual ~Load_Scene();

	void Init();
	SceneBase* Update(SceneRoot* root);
	void Render();
	void Destroy();
};