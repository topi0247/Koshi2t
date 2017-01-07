#pragma once
#include <iostream>
#include <map>
#include <string>
#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"
#include "./../../UI/TD_Graphics.h"
#include "./../SceneParts/CharactorSelection_Scene.h"
#include "./../../Charactor/Player/GamePad.h"

class Title_Scene :public Scene
{
private:
	std::map<std::string, TD_Graphics*> title_UI;
public:
	Title_Scene();
	~Title_Scene();

	void Init();
	SceneBase* Update(SceneRoot* root);
	void Render();
	void Destroy();
};