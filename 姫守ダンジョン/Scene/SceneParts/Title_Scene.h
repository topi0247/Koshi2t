#pragma once
#include <iostream>
#include <map>
#include <string>
#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"
#include "./../SceneParts/CharactorSelection_Scene.h"
#include "./../SceneParts/Load_Scene.h"
#include "./../../Mesh/CD3DXSKINMESH.h"
#include "./../../Charactor/CharactorCreator.h"
#include "./../../Camera.h"

#ifdef _DEBUG
#include "./Main_Scene.h"
#endif //_DEBUG

#define enemyInsRange 50
#define oneEnemyMax 10
#define enemyMax oneEnemyMax*3
class Title_Scene :public Scene
{
private:
	float alfa_;

	std::map<std::string, TD_Graphics*> title_UI;
	CD3DXSKINMESH* mesh_sword_;
	CD3DXSKINMESH* mesh_shiled_;
	CD3DXSKINMESH* mesh_bomber_;
	CD3DXSKINMESH* mesh_witch_;
	CD3DXSKINMESH* mesh_princess_;
	CD3DXSKINMESH* mesh_slime_;
	CD3DXSKINMESH* mesh_goblin_;
	CD3DXSKINMESH* mesh_skelton_;
	std::vector<CD3DXSKINMESH*> mesh_enemyList_;
	CD3DXMESH* mesh_stage_;

	Camera* camera_;
	CharactorCreator* creator_;
	D3DXVECTOR3 enemyPos_[enemyMax];
	float enemyRot_[enemyMax];
	void DebugSetJob();
public:
	Title_Scene();
	virtual ~Title_Scene();

	void Init();
	SceneBase* Update(SceneRoot* root);
	void Render();
	void Destroy();
};