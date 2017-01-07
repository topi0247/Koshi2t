#include "./Title_Scene.h"


Title_Scene::Title_Scene()
{
}

Title_Scene::~Title_Scene()
{
}

void Title_Scene::Init()
{
}

void Title_Scene::Destroy()
{
}

SceneBase* Title_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;

	if (GetKeyState(VK_F1) & 0x80)
	{
		next = new CharactorSelection_Scene;
	}

	return next;
}

void Title_Scene::Render()
{
}