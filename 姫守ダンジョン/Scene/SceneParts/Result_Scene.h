#pragma once
#include <iostream>
#include <map>
#include <string>
#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"
#include "./../SceneParts/Title_Scene.h"
#include "./../SceneParts/Main_Scene.h"
#include "./../../Mesh/CD3DXSKINMESH.h"
#include "./../../Charactor/CharactorCreator.h"
#include "./../../Camera.h"
#include "./../../UI/D3D11_SPRITE.h"

class Result_Scene :public Scene
{
private:

	CD3DXSKINMESH* mesh_princess_;
	CD3DXMESH* mesh_stage_;

	D3D11_TEXT* debugText_;

	Camera* camera_;

	CD3DXSKINMESH* meshPlayer1_;
	CD3DXSKINMESH* meshPlayer2_;
	CD3DXSKINMESH* meshPlayer3_;
	CD3DXSKINMESH* meshPlayer4_;
	CharactorCreator* creator_;

public:
	Result_Scene();
	virtual ~Result_Scene();

	void Init();
	SceneBase* Update(SceneRoot* root);
	void Render();
	void Destroy();
};