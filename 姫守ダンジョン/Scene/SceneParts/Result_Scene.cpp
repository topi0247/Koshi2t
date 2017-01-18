#include "./Result_Scene.h"

Result_Scene::Result_Scene()
{
	//new
	camera_ = new Camera;
	creator_ = new CharactorCreator;
	debugText_ = new D3D11_TEXT;
}

Result_Scene::~Result_Scene()
{
	//delete
	delete camera_;
	camera_ = nullptr;
	delete creator_;
	creator_ = nullptr;

	delete debugText_;
	debugText_ = nullptr;
}

void Result_Scene::Init()
{
	float scale = 5;
	float dist = 5;
	float speed = 1.0f / 40.0f;

	//読み込み
	camera_->gazePoint_ = D3DXVECTOR3(0, 5.5, 0);
	camera_->movePow_ = D3DXVECTOR3(0, 5.8, -28);

	meshPlayer1_ = creator_->LoadChara(CharactorCreator::player1_);
	meshPlayer2_ = creator_->LoadChara(CharactorCreator::player2_);
	meshPlayer3_ = creator_->LoadChara(CharactorCreator::player3_);
	meshPlayer4_ = creator_->LoadChara(CharactorCreator::player4_);

	mesh_princess_ = creator_->LoadChara("姫");

	mesh_stage_ = creator_->LoadStage("タイトル");
}

void Result_Scene::Destroy()
{
	SAFE_DELETE(mesh_princess_);
}

SceneBase* Result_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;

	static bool nextSceneFlg = false;

	for (int i = 0; i < 4; i++)
	{
		if (GamePad::checkInput(i, GamePad::InputName::B)/*GetKeyState(VK_SPACE) & 0x80*/)
		{
			nextSceneFlg = true;
		}
	}

	if (nextSceneFlg)
	{
		next = new Title_Scene;
		nextSceneFlg = false;
	}

	GamePad::update();
	return next;
}

void Result_Scene::Render()
{
	float scale = 0.5;
	float dist = 5;
	float speed = 1.0f / 40.0f;
	float sp = 0.001;

	meshPlayer1_->Render(D3DXVECTOR3(-dist, 0, 0), 0, D3DXVECTOR3(scale, scale, scale));
	meshPlayer1_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	meshPlayer2_->Render(D3DXVECTOR3(dist, 0, 0), 0, D3DXVECTOR3(scale, scale, scale));
	meshPlayer2_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	meshPlayer3_->Render(D3DXVECTOR3(-dist - 5, 0, 0), 0, D3DXVECTOR3(scale, scale, scale));
	meshPlayer3_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	meshPlayer4_->Render(D3DXVECTOR3(dist + 5, 0, 0), 0, D3DXVECTOR3(scale, scale, scale));
	meshPlayer4_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);


	mesh_princess_->Render(D3DXVECTOR3(0, 0, 0), 0, D3DXVECTOR3(scale, scale, scale), camera_->movePow_);
	mesh_princess_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);

	camera_->movePow_.x += (GetKeyState(VK_LEFT) & 0x80)*sp + -(GetKeyState(VK_RIGHT) & 0x80)*sp;
	camera_->movePow_.y += (GetKeyState('W') & 0x80)*sp + -(GetKeyState('S') & 0x80)*sp;
	camera_->movePow_.z += (GetKeyState(VK_UP) & 0x80)*sp + -(GetKeyState(VK_DOWN) & 0x80)*sp;

	//ステージの描画
	mesh_stage_->Render(D3DXVECTOR3(0, 0.8, 0), D3DXVECTOR3(0, 0, 0), 2);

	char str[256];
	sprintf(str, "pos.x:%f pos.y:%f pos.z:%f", camera_->movePow_.x, camera_->movePow_.y, camera_->movePow_.z);
	debugText_->Render(str, 0, 50);

	camera_->Render();
}