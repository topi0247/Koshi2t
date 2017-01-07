#pragma once
#include <iostream>
#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"
#include "./Title_Scene.h"
#include "./CharactorSelection_Scene.h"

class Result_Scene :public Scene
{
public:
	Result_Scene();
	~Result_Scene();

	void Init();
	SceneBase* Update(SceneRoot* root);
	void Render();
	void Destroy();
};