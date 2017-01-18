#pragma once
#include <iostream>
#include <map>
#include <string>
#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"
#include "./../SceneParts/Main_Scene.h"
#include "./../SceneParts/Title_Scene.h"
#include "./../../Charactor/CharactorCreator.h"
#include "./../../DebugDraw/D3D11_TEXT.h"

#define null "null"

class CharactorSelection_Scene : public Scene
{
private:
	enum jobName
	{
		sword = 0,
		shield,
		bomber,
		witch,
		not= 100,
	};
	std::map<std::string, TD_Graphics*> charaSelect_UI;
	CharactorCreator* creator_;
	CD3DXSKINMESH* sword_;
	CD3DXSKINMESH* shield_;
	CD3DXSKINMESH* bomber_;
	CD3DXSKINMESH* witch_;
	Camera* camera_;
	D3D11_TEXT* text_;

	bool nextFlg_;
	int okButon_;
	int keyWait_[4];
	jobName choiceJob_[4];
	D3DXVECTOR2 playerUIPos_[4];
	D3DXVECTOR3 meshPos_[4];

	D3DXVECTOR2 Move(int type);
	void SetCharaJob(int type);
	void DecideJob();
	void CancelJob(int type);
	void Update();
	void MeshRender(jobName name, int type);
	void ChoiceJobUIRender(jobName, int type);
	float HandAnimation(float size);
	D3DXVECTOR2 StartAnimation(D3DXVECTOR2 pos);

public:
	CharactorSelection_Scene();
	virtual ~CharactorSelection_Scene();

	void Init();
	SceneBase* Update(SceneRoot* root);
	void Render();
	void Destroy();
};