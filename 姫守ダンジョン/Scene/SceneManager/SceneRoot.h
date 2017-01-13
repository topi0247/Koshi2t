#pragma once
#include <assert.h>
#include <iostream>
#include "./../SceneManager/SceneRoot.h"
#include "./../SceneParts/Scene.h"
#include "./../SceneParts/Title_Scene.h"

class SceneRoot :public SceneBase
{
public:
	//enum Mode
	//{
	//	kTitle='1',
	//	kMain='2',
	//	kNone
	//};
	SceneRoot();
	~SceneRoot();

	void Init();
	SceneBase* Update(SceneBase* scene);
	void Render();
	void Destroy();

private:
	Scene* scene_;
	Scene* loadScene_;
	Scene* nextScene_;
	//Mode mode_;
};