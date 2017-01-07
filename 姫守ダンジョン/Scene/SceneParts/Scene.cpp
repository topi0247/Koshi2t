#include <assert.h>

#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"

SceneBase* Scene::Update(SceneBase* scene)
{
	SceneRoot* root = dynamic_cast<SceneRoot*>(scene);
	assert(root);
	return Update(root);
}