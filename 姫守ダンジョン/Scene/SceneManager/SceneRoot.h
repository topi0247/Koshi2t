#pragma once
#include <assert.h>
#include <iostream>
#include <process.h>	//	マルチスレッド
#include "./../SceneManager/SceneRoot.h"
#include "./../SceneParts/Scene.h"
#include "./../SceneParts/Title_Scene.h"
#include "./../SceneParts/Load_Scene.h"

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
	static unsigned int WINAPI ThreadFunc(LPVOID arg);

private:
	Scene* scene_;
	Scene* loadScene_;
	static Scene* beforeScene_;
	static Scene* nextScene_;
	static bool loadFlg_;

	static void Load();
	
	//Mode mode_;
};
