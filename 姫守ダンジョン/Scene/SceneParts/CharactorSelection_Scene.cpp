#include "./CharactorSelection_Scene.h"

CharactorSelection_Scene::CharactorSelection_Scene()
{

}

CharactorSelection_Scene::~CharactorSelection_Scene()
{

}

void CharactorSelection_Scene::Init()
{

}

void CharactorSelection_Scene::Destroy()
{

}

SceneBase* CharactorSelection_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;

	if (GetKeyState(VK_F2) & 0x80)
	{
		next = new Main_Scene;
	}

	return next;
}

void CharactorSelection_Scene::Render()
{

}