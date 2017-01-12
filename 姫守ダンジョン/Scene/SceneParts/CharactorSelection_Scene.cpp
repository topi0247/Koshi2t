#include "./CharactorSelection_Scene.h"

CharactorSelection_Scene::CharactorSelection_Scene()
{
	charaSelect_UI["CHARASELECT_UI"] = new TD_Graphics;
	charaSelect_UI["FINGER_UI"] = new TD_Graphics;

	camera_ = new Camera;
	text_ = new D3D11_TEXT;
}

CharactorSelection_Scene::~CharactorSelection_Scene()
{
	delete charaSelect_UI["CHARASELECT_UI"];
	charaSelect_UI["CHARASELECT_UI"] = nullptr;
	delete charaSelect_UI["FINGER_UI"];
	charaSelect_UI["FINGER_UI"] = nullptr;
	delete camera_;
	camera_ = nullptr;
	delete text_;
	text_ = nullptr;
}

void CharactorSelection_Scene::Init()
{
	nextFlg_ = false;
	okButon_ = 10;
	strcpy(CharactorCreator::player1_, null);
	strcpy(CharactorCreator::player2_, null);
	strcpy(CharactorCreator::player3_, null);
	strcpy(CharactorCreator::player4_, null);
	CharactorCreator* creator = new CharactorCreator;
	sword_ = creator->GetCharaModel("Œ•Žm");
	shield_ = creator->GetCharaModel("‚Žm");
	bomber_ = creator->GetCharaModel("”š’eŽm");
	witch_ = creator->GetCharaModel("–‚“±Žm");

	for (int i = 0; i < 4; i++)
	{
		choiceJob_[i] = not;
		keyWait_[i] = 0;
		pos_[i] = D3DXVECTOR2(100 + i * 500, 50);
		meshPos_[i] = D3DXVECTOR3(-3 + i * 2, 0, 0);
	}

	charaSelect_UI["FINGER_UI"]->Init(L"./UI/UI_Tex/finger.png", /*0,*/ D3DXVECTOR2(0, 0), D3DXVECTOR2(115, 150), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["CHARASELECT_UI"]->Init(L"./UI/UI_Tex/character_select.png",/* 0,*/ D3DXVECTOR2(0, 0), D3DXVECTOR2(WINDOW_WIDTH, WINDOW_HEIGHT), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));

	Camera::gazePoint_ = D3DXVECTOR3(0, 2.4, 0);
	Camera::movePow_ = D3DXVECTOR3(0, 2.4, -10);
}

void CharactorSelection_Scene::Destroy()
{

}

SceneBase* CharactorSelection_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;
	Update();


	if (nextFlg_)
	{
		for (int i = 0; i < 4; i++)
		{
			if (keyWait_[i] > okButon_ && GamePad::checkInput(i, GamePad::InputName::A))
			{
				DecideJob();
				next = new Main_Scene;
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (keyWait_[i] > okButon_ && GamePad::checkInput(i, GamePad::InputName::B))
			{
				next = new Title_Scene;
			}
		}
	}

	//int andPlayer = Player1 & Player2 & Player3 & Player4;
	//if (nextFlg_ && GamePad::checkInput(andPlayer, GamePad::InputName::A))
	//{
	//	next = new Main_Scene;
	//}

	/*static bool backFlg = false;
	if (!backFlg)
	{
		for (int i = 0; i < 4; i++)
		{
			if (keyWait_[i] > okButon_ && choiceJob_[i] == not && GamePad::checkInput(i, GamePad::InputName::B))
			{
				backFlg = true;
			}
		}

	}
	if (backFlg)
	{
		next = new Title_Scene;
		backFlg = false;
	}*/

	GamePad::update();
	return next;
}

void CharactorSelection_Scene::Update()
{
	for (int i = 0; i < 4; i++)
	{
		++keyWait_[i];
		pos_[i] = Move(i);
		if (keyWait_[i] > okButon_)
		{
			if (!nextFlg_ && GamePad::checkInput(i, GamePad::InputName::A))
			{
				SetCharaJob(i);
				keyWait_[i] = 0;
			}
			if (choiceJob_[i] != not&&GamePad::checkInput(i, GamePad::InputName::B))
			{
				CancelJob(i);
				keyWait_[i] = 0;
			}
		}
	}

	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (choiceJob_[i] != not)
		{
			++count;
		}
	}
	if (count == 4)
	{
		nextFlg_ = true;
	}
	else
	{
		nextFlg_ = false;
	}
}

D3DXVECTOR2 CharactorSelection_Scene::Move(int type)
{
	//ƒXƒeƒBƒbƒN‚ÌŒX‚«Žæ“¾
	D3DXVECTOR2 temp = pos_[type];
	D3DXVECTOR2 inputStick(0, 0);
	float stopRange = 0.3;
	inputStick.x = GamePad::getAnalogValue(type, GamePad::AnalogName::AnalogName_LeftStick_X);
	inputStick.y = -GamePad::getAnalogValue(type, GamePad::AnalogName::AnalogName_LeftStick_Y);

	if (fabsf(inputStick.x) < stopRange)
	{
		inputStick.x = 0;
	}
	if (fabsf(inputStick.y) < stopRange)
	{
		inputStick.y = 0;
	}

	float speed = 40;
	temp += inputStick*speed;
	if (temp.x < 0 || temp.x>WINDOW_WIDTH - 115)
	{
		temp.x = pos_[type].x;
	}
	if (temp.y < 0 || temp.y>WINDOW_HEIGHT - 150)
	{
		temp.y = pos_[type].y;
	}

	return temp;

}

void CharactorSelection_Scene::SetCharaJob(int type)
{
	//À•W‚ÉŠî‚Ã‚­ƒLƒƒƒ‰ƒNƒ^[‘I‘ð
	jobName temp = not;
	float up = 256;
	float down = 890;
	if (pos_[type].x > 21 && pos_[type].x < 470
		&& pos_[type].y >up && pos_[type].y < down)
	{
		temp = sword;
	}
	else if (pos_[type].x > 493 && pos_[type].x < 950
		&& pos_[type].y > up && pos_[type].y < down)
	{
		temp = shield;
	}
	else if (pos_[type].x > 970 && pos_[type].x < 1423
		&& pos_[type].y > up && pos_[type].y < down)
	{
		temp = bomber;
	}
	else if (pos_[type].x > 1444 && pos_[type].x < 1900
		&& pos_[type].y > up && pos_[type].y < down)
	{
		temp = witch;
	}
	else
	{
		return;
	}

	choiceJob_[type] = temp;
}

void CharactorSelection_Scene::DecideJob()
{
	for (int i = 0; i < 4; i++)
	{
		char name[10];
		switch (choiceJob_[i])
		{
		case sword:
			strcpy(name, "Œ•Žm");
			break;
		case shield:
			strcpy(name, "‚Žm");
			break;
		case bomber:
			strcpy(name, "”š’eŽm");
			break;
		case witch:
			strcpy(name, "–‚“±Žm");
			break;
		default:
			break;
		}

		switch (i)
		{
		case Player1:
			strcpy(CharactorCreator::player1_, name);
			break;
		case Player2:
			strcpy(CharactorCreator::player2_, name);
			break;
		case Player3:
			strcpy(CharactorCreator::player3_, name);
			break;
		case Player4:
			strcpy(CharactorCreator::player4_, name);
			break;
		default:
			break;
		}
	}
}

void CharactorSelection_Scene::CancelJob(int type)
{
	choiceJob_[type] = not;
}

D3DXVECTOR2 CharactorSelection_Scene::HandAnimation(D3DXVECTOR2 size)
{
	static D3DXVECTOR2 scale(1, 1);
	static bool big = true;
	float mag = 0.01;
	D3DXVECTOR2 maxScale(1.3, 1.3);
	D3DXVECTOR2 minScale(0.8, 0.8);

	if (size > maxScale)
	{
		big = false;
	}
	else if (size < minScale)
	{
		big = true;
	}

	if (big)
	{
		scale += D3DXVECTOR2(mag, mag);
	}
	else
	{
		scale -= D3DXVECTOR2(mag, mag);
	}

	return scale;
}

void CharactorSelection_Scene::MeshRender(jobName name, int type)
{

	D3DXVECTOR3 pos(meshPos_[type].x, meshPos_[type].y, meshPos_[type].z);
	float scale = 0.2;
	float speed = 1.0f / 40.0f;
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
}

void CharactorSelection_Scene::Render()
{


	/*static */D3DXVECTOR2 size(1, 1);
	//size = HandAnimation(size);
	//pos_[0].x += 0.1f;
	for (int i = 0; i < 4; i++)
	{
		charaSelect_UI["FINGER_UI"]->Render(pos_[i], size, true);
	}

	//static D3DXVECTOR2 mag(1, 1);
	//mag.x += -(GetKeyState(VK_LEFT) & 0x80)*0.001f+ (GetKeyState(VK_RIGHT) & 0x80)*0.001f;
	//mag.y += -(GetKeyState(VK_UP) & 0x80)*0.001f + (GetKeyState(VK_DOWN) & 0x80)*0.001f;


	charaSelect_UI["CHARASELECT_UI"]->Render(D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1), false);

	float scale = 0.15;
	float y = 1.5;
	float speed = 1.0f / 40.0f;
	sword_->Render(D3DXVECTOR3(-4, y, 1), 0, D3DXVECTOR3(scale, scale, scale));
	//sword_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	shield_->Render(D3DXVECTOR3(-1, y, 1), 0, D3DXVECTOR3(scale, scale, scale));
	//shield_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	bomber_->Render(D3DXVECTOR3(1, y, 1), 0, D3DXVECTOR3(scale, scale, scale));
	//bomber_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	witch_->Render(D3DXVECTOR3(3.5, y, 1), 0, D3DXVECTOR3(scale, scale, scale));
	//witch_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);


	for (int i = 0; i < 4; i++)
	{
		MeshRender(choiceJob_[i], i);
	}

	//ƒ‚[ƒVƒ‡ƒ“
	sword_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	shield_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	bomber_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	witch_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);

	camera_->Render();


	////ƒfƒoƒbƒO•`‰æ
	//char str[256];
	//sprintf(str, "mag.x:%f mag.y:%f",mag.x,mag.y);
	//text_->Render(str, 0, 50);


}