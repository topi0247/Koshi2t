#pragma once
#include <iostream>
#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"
#include "./../SceneParts/Main_Scene.h"

class CharactorSelection_Scene : public Scene
{
public:
	CharactorSelection_Scene();
	~CharactorSelection_Scene();

	void Init();
	SceneBase* Update(SceneRoot* root);
	void Render();
	void Destroy();
};