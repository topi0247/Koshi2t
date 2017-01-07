#pragma once
#include <iostream>
#include <map>
#include <string>
#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"
#include "./../SceneParts/Main_Scene.h"
#include "./../SceneParts/Title_Scene.h"
#include "./../../Charactor/Player/GamePad.h"

class CharactorSelection_Scene : public Scene
{
private:
	std::map<std::string, TD_Graphics*> charaSelect_UI;

public:
	CharactorSelection_Scene();
	~CharactorSelection_Scene();

	void Init();
	SceneBase* Update(SceneRoot* root);
	void Render();
	void Destroy();
};