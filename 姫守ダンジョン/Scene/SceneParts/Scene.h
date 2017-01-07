#pragma once
#include "./../Bass/SceneBase.h"

class SceneRoot;

class Scene :public SceneBase
{
public: 
	virtual ~Scene() {};

	SceneBase* Update(SceneBase* scene);
	virtual SceneBase* Update(SceneRoot* root) = 0;
};
