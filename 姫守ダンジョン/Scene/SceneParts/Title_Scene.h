#pragma once
#include <iostream>
#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"
#include "./../SceneParts/CharactorSelection_Scene.h"

class Title_Scene :public Scene
{
public:
	Title_Scene();
	~Title_Scene();

	void Init();
	SceneBase* Update(SceneRoot* root);
	void Render();
	void Destroy();
};