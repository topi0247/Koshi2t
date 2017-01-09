#include "./CharactorSelection_Scene.h"

CharactorSelection_Scene::CharactorSelection_Scene()
{
	charaSelect_UI["CHARASELECT_UI"] = new TD_Graphics;
	charaSelect_UI["FINGER_UI"] = new TD_Graphics;

	camera_ = new Camera;
}

CharactorSelection_Scene::~CharactorSelection_Scene()
{
	delete charaSelect_UI["CHARASELECT_UI"];
	delete charaSelect_UI["FINGER_UI"];
	delete camera_;
	camera_ = nullptr;
}

void CharactorSelection_Scene::Init()
{
	nextFlg_ = false;
	strcpy(CharactorCreator::player1_, null);
	strcpy(CharactorCreator::player2_, null);
	strcpy(CharactorCreator::player3_, null);
	strcpy(CharactorCreator::player4_, null);
	for (int i = 0; i < 4; i++)
	{
		choiceJob_[i] = not;
		pos_[i] = D3DXVECTOR2(0, 0);
		meshPos_[i] = D3DXVECTOR3(-15 + i * 5, 0, 0);
	}

	charaSelect_UI["CHARASELECT_UI"]->Init(L"./UI/UI_Tex/character_select.png", 0, D3DXVECTOR2(0, 0), D3DXVECTOR2(1920, 1080), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["FINGER_UI"]->Init(L"./UI/UI_Tex/finger.png", 0, D3DXVECTOR2(0, 0), D3DXVECTOR2(230, 300), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));

	Camera::gazePoint_ = D3DXVECTOR3(0, 0, 0);
	Camera::movePow_ = D3DXVECTOR3(0, 0, -30);
}

void CharactorSelection_Scene::Destroy()
{

}

SceneBase* CharactorSelection_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;

	Update();

	//int andPlayer = Player1 & Player2 & Player3 & Player4;
	//if (nextFlg_ && GamePad::checkInput(andPlayer, GamePad::InputName::A))
	//{
	//	next = new Main_Scene;
	//}

	int orPlayer = Player1 | Player2 | Player3 | Player4;
	if (!nextFlg_ && GamePad::checkInput(orPlayer, GamePad::InputName::B))
	{
		next = new Title_Scene;
	}
	GamePad::update();
	return next;
}

void CharactorSelection_Scene::Update()
{
	float speed = 0.01;
	for (int i = 0; i < 4; i++)
	{
		D3DXVECTOR2 pos = Move(i);
		if (pos_[i].x > 0 && pos_[i].x < WINDOW_WIDTH)
		{
			pos_[i].x += pos.x*speed;
		}
		if (pos_[i].y < 0 && pos_[i].y < WINDOW_HEIGHT)
		{
			pos_[i].y += pos.y*speed;
		}

		if (GamePad::checkInput(i, GamePad::InputName::A))
		{
			SetCharaJob(i);
		}
		if (GamePad::checkInput(i, GamePad::InputName::B))
		{
			CancelJob(i);
		}
	}

	for (int i=0; i < 4; i++)
	{
		if (choiceJob_[i] == not)
		{
			break;
		}
		nextFlg_ = true;
	}
}

D3DXVECTOR2 CharactorSelection_Scene::Move(int type)
{
	//スティックの傾き取得
	D3DXVECTOR2 inputStick;
	inputStick.x = GamePad::getAnalogValue(type, GamePad::AnalogName::AnalogName_LeftStick_X);
	inputStick.y = GamePad::getAnalogValue(type, GamePad::AnalogName::AnalogName_LeftStick_Y);

	return inputStick;

}

void CharactorSelection_Scene::SetCharaJob(int type)
{
	//座標に基づくキャラクター選択
	jobName temp = not;
	if (pos_[type].x<0 && pos_[type].x>WINDOW_WIDTH
		&& pos_[type].y<0 && pos_[type].y>200)
	{
		temp = sword;
	}
	else if (pos_[type].x<0 && pos_[type].x>WINDOW_WIDTH
		&& pos_[type].y<250 && pos_[type].y>450)
	{
		temp = shield;
	}
	else if (pos_[type].x<0 && pos_[type].x>WINDOW_WIDTH
		&& pos_[type].y<500 && pos_[type].y>700)
	{
		temp = bomber;
	}
	else if (pos_[type].x<0 && pos_[type].x>WINDOW_WIDTH
		&& pos_[type].y<750 && pos_[type].y>950)
	{
		temp = witch;
	}
	else
	{
		return;
	}

	choiceJob_[type] = temp;
}

void CharactorSelection_Scene::CancelJob(int type)
{
	choiceJob_[type] = not;
}

void CharactorSelection_Scene::MeshRender(jobName name, int type)
{
	if (name == not)
	{
		return;
	}

	D3DXVECTOR3 pos(meshPos_[type].x, meshPos_[type].y, meshPos_[type].z);
	float scale = 0.2;
	switch (name)
	{
	case sword:
		sword_->Render(pos, 0, D3DXVECTOR3(scale, scale, scale));
		break;
	case shield:
		shield_->Render(pos, 0, D3DXVECTOR3(scale, scale, scale));
		break;
	case bomber:
		bomber_->Render(pos, 0, D3DXVECTOR3(scale, scale, scale));
		break;
	case witch:
		witch_->Render(pos, 0, D3DXVECTOR3(scale, scale, scale));
		break;
	default:
		break;
	}
	camera_->Render();
}

void CharactorSelection_Scene::Render()
{
	//charaSelect_UI["CHARASELECT_UI"]->Render(0, 0, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		charaSelect_UI["FINGER_UI"]->Render(0, 0, pos_[i].x, pos_[i].y);
	}
}