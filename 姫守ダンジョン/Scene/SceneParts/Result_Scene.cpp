#include "./Result_Scene.h"

Result_Scene::Result_Scene()
{

}

Result_Scene::~Result_Scene()
{

}

void Result_Scene::Init()
{

}

void Result_Scene::Destroy()
{

}

SceneBase* Result_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;

	if (GetKeyState(VK_F3) & 0x80)
	{
		next = new Title_Scene;
	}

	return this;
}

void Result_Scene::Render()
{

}