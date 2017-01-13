#include "./SceneRoot.h"
#include "./../SceneParts/Main_Scene.h"

SceneRoot::SceneRoot()
	:scene_(nullptr)
	//,mode_(kNone)
{
}

SceneRoot::~SceneRoot()
{
}


void SceneRoot::Init()
{
	//std::cout << "SceneRoot::Startup()" << std::endl;

	//scene_ = new SceneTitle();

	loadScene_ = new Load_Scene;
	scene_ = new Title_Scene;
	scene_->Init();
}

void SceneRoot::Destroy()
{
	//std::cout << "SceneRoot::Shutdown()" << std::endl;
	delete loadScene_;
	delete scene_;
	//scene_ = nullptr;
}

SceneBase* SceneRoot::Update(SceneBase* scene)
{
	//std::cout << "SceneRoot::Update(SceneBase)" << std::endl;

	//if (getchar() == 'q')
	//{
	//	return nullptr;
	//}

	//シーンの実行
	SceneBase* next = scene_->Update(this);

	//戻り値が現在のシーンと異なっていればシーン切り替え処理
	if (next != scene_)
	{
		Scene* casted = dynamic_cast<Scene*>(next);
		assert(casted);

		scene_->Destroy();
		delete scene_;
		
		//next = loadScene_;
		scene_ = loadScene_;
		//scene_ = new Load_Scene;
		scene_->Init();
		nextScene_ = casted;
		//next->Init();
	}
	if (next == loadScene_)
	{
		static int count = 0;
		if (++count%(FPS * 1) == 0)
		{
			//scene_->Destroy();
			//delete scene_;
			scene_ = nextScene_;
			scene_->Init();
			//delete nextScene_;
			count = 0;
		}
	}

	return this;
}

void SceneRoot::Render()
{
	scene_->Render();
}