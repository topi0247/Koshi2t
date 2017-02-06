#include "./CharactorSelection_Scene.h"


CharactorSelection_Scene::CharactorSelection_Scene()
{
	charaSelect_UI["CHARASELECT_UI"] = new TD_Graphics;
	charaSelect_UI["player1"] = new TD_Graphics;
	charaSelect_UI["player2"] = new TD_Graphics;
	charaSelect_UI["player3"] = new TD_Graphics;
	charaSelect_UI["player4"] = new TD_Graphics;
	charaSelect_UI["beforeButton"] = new TD_Graphics;
	charaSelect_UI["decideButton"] = new TD_Graphics;
	camera_ = new Camera;
	text_ = new D3D11_TEXT;
	creator_ = new CharactorCreator;
}

CharactorSelection_Scene::~CharactorSelection_Scene()
{
	delete charaSelect_UI["CHARASELECT_UI"];
	charaSelect_UI["CHARASELECT_UI"] = nullptr;
	delete charaSelect_UI["FINGER_UI"];
	charaSelect_UI["FINGER_UI"] = nullptr;
	delete charaSelect_UI["player1"];
	charaSelect_UI["player1"] = nullptr;
	delete charaSelect_UI["player2"];
	charaSelect_UI["player2"] = nullptr;
	delete charaSelect_UI["player3"];
	charaSelect_UI["player3"] = nullptr;
	delete charaSelect_UI["player4"];
	charaSelect_UI["player4"] = nullptr;
	delete charaSelect_UI["beforeButton"];
	charaSelect_UI["beforeButton"] = nullptr;
	delete charaSelect_UI["decideButton"];
	charaSelect_UI["decideButton"] = nullptr;

	delete creator_;
	creator_ = nullptr;
	delete camera_;
	camera_ = nullptr;
	delete text_;
	text_ = nullptr;
}

void CharactorSelection_Scene::Init()
{
	nextFlg_ = false;
	okButon_ = 20;
	strcpy(CharactorCreator::player1_, null);
	strcpy(CharactorCreator::player2_, null);
	strcpy(CharactorCreator::player3_, null);
	strcpy(CharactorCreator::player4_, null);

	sword_ = creator_->LoadChara("åïém");
	shield_ = creator_->LoadChara("èÇém");
	bomber_ = creator_->LoadChara("îöíeém");
	witch_ = creator_->LoadChara("ñÇì±ém");

	for (int i = 0; i < 4; i++)
	{
		choiceJob_[i] = not;
		keyWait_[i] = 0;
		playerUIPos_[i] = D3DXVECTOR2(50 + i * 500, 890);
		meshPos_[i] = D3DXVECTOR3(-3.5 + i * 2, 0.32, 0);
	}

	charaSelect_UI["player1"]->Init(L"./UI/UI_Tex/player_plate1.png", D3DXVECTOR2(115, 150), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["player2"]->Init(L"./UI/UI_Tex/player_plate2.png",D3DXVECTOR2(115, 150), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["player3"]->Init(L"./UI/UI_Tex/player_plate3.png",  D3DXVECTOR2(115, 150), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["player4"]->Init(L"./UI/UI_Tex/player_plate4.png", D3DXVECTOR2(115, 150), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["CHARASELECT_UI"]->Init(L"./UI/UI_Tex/character_select.png", D3DXVECTOR2(WINDOW_WIDTH, WINDOW_HEIGHT), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));

	D3DXVECTOR2 size(250, 350);
	charaSelect_UI["beforeButton"]->Init(L"./UI/UI_Tex/CS_start_off.png", size, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["decideButton"]->Init(L"./UI/UI_Tex/CS_start_on1.png", size, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	camera_->gazePoint_ = D3DXVECTOR3(0, 2.4, 0);
	camera_->movePow_ = D3DXVECTOR3(0, 2.4, -10);
	Sound::getInstance().BGM_play("CHARACTERSELECT");
}

void CharactorSelection_Scene::Destroy()
{
	Sound::getInstance().BGM_stop("CHARACTERSELECT");
	SAFE_DELETE(sword_);
	SAFE_DELETE(shield_);
	SAFE_DELETE(bomber_);
	SAFE_DELETE(witch_);
}
//å„Ç≈è¡Ç∑(î≠ï\óp)
#include "./Result_Scene.h"
SceneBase* CharactorSelection_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;
	Update();


	if (nextFlg_)
	{
		for (int i = 0; i < 4; i++)
		{
			if (keyWait_[i] < okButon_)
			{
				break;
			}
			else if (keyWait_[i] > okButon_ && GamePad::checkInput(i, GamePad::InputName::A))
			{
				if (playerUIPos_[i].x > 1660 && playerUIPos_[i].x < 1835
					&& playerUIPos_[i].y>680 && playerUIPos_[i].y < 1020)
				{
					DecideJob();
					next = new Main_Scene;
					Sound::getInstance().SE_play("DECISION_SE");
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (keyWait_[i] < okButon_)
			{
				break;
			}
			else if (keyWait_[i] > okButon_ && GamePad::checkInput(i, GamePad::InputName::BACK))
			{
				next = new Title_Scene;
			}
		}
	}

	if (GamePad::checkInput(Player1, GamePad::InputName::RB))
	{
		strcpy(CharactorCreator::player1_, "åïém");
		strcpy(CharactorCreator::player2_, "èÇém");
		strcpy(CharactorCreator::player3_, "îöíeém");
		strcpy(CharactorCreator::player4_, "ñÇì±ém");
		Result_Scene::m10_Time = 1;
		Result_Scene::m1_Time = 2;
		Result_Scene::s10_Time = 3;
		Result_Scene::s1_Time = 4;
		Result_Scene::c10_Time = 5;
		Result_Scene::c1_Time = 6;
		Result_Scene::clearFlg_ = true;
		next = new Result_Scene;
	}
	if (GamePad::checkInput(Player1, GamePad::InputName::LB))
	{
		strcpy(CharactorCreator::player1_, "åïém");
		strcpy(CharactorCreator::player2_, "èÇém");
		strcpy(CharactorCreator::player3_, "îöíeém");
		strcpy(CharactorCreator::player4_, "ñÇì±ém");
		Result_Scene::clearFlg_ = false;
		next = new Result_Scene;
	}

	GamePad::update();
	return next;
}

void CharactorSelection_Scene::Update()
{

	for (int i = 0; i < 4; i++)
	{
		++keyWait_[i];
		playerUIPos_[i] = Move(i);
		if (keyWait_[i] > okButon_)
		{
			if (GamePad::checkInput(i, GamePad::InputName::A))
			{
				SetCharaJob(i);
				if (!nextFlg_)
				{
					keyWait_[i] = 0;
				}
			}
			if (choiceJob_[i] != not&&GamePad::checkInput(i, GamePad::InputName::B))
			{
				CancelJob(i);
				keyWait_[i] = 0;
			}
		}
	}

	//#ifdef _DEBUG
	if (GamePad::checkInput(Player1, GamePad::InputName::RT))
	{
		choiceJob_[Player2] = shield;
		choiceJob_[Player3] = bomber;
		choiceJob_[Player4] = witch;
	}
	if (GetKeyState('S') & 0x80)
	{
		choiceJob_[Player1] = sword;
		choiceJob_[Player2] = shield;
		choiceJob_[Player3] = bomber;
		choiceJob_[Player4] = witch;
	}
	if (GamePad::checkInput(Player1, GamePad::InputName::LT))
	{
		choiceJob_[Player2] = not;
		choiceJob_[Player3] = not;
		choiceJob_[Player4] = not;
	}
	if (GetKeyState('R') & 0x80)
	{
		choiceJob_[Player1] = not;
		choiceJob_[Player2] = not;
		choiceJob_[Player3] = not;
		choiceJob_[Player4] = not;
	}
	//#endif

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
	//ÉXÉeÉBÉbÉNÇÃåXÇ´éÊìæ
	D3DXVECTOR2 temp = playerUIPos_[type];
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
		temp.x = playerUIPos_[type].x;
	}
	if (temp.y < 0 || temp.y>WINDOW_HEIGHT - 150)
	{
		temp.y = playerUIPos_[type].y;
	}

	return temp;

}

void CharactorSelection_Scene::SetCharaJob(int type)
{
	//ç¿ïWÇ…äÓÇ√Ç≠ÉLÉÉÉâÉNÉ^Å[ëIë
	jobName temp = not;
	float up = 170;
	float down = 625;
	if (playerUIPos_[type].x > 30 && playerUIPos_[type].x < 470
		&& playerUIPos_[type].y >up && playerUIPos_[type].y < down)
	{
		temp = sword;
		Sound::getInstance().SE_play("DECISION_SE");
	}
	else if (playerUIPos_[type].x > 500 && playerUIPos_[type].x < 940
		&& playerUIPos_[type].y > up && playerUIPos_[type].y < down)
	{
		temp = shield;
		Sound::getInstance().SE_play("DECISION_SE");
	}
	else if (playerUIPos_[type].x > 970 && playerUIPos_[type].x < 1415
		&& playerUIPos_[type].y > up && playerUIPos_[type].y < down)
	{
		temp = bomber;
		Sound::getInstance().SE_play("DECISION_SE");
	}
	else if (playerUIPos_[type].x > 1450 && playerUIPos_[type].x < 1890
		&& playerUIPos_[type].y > up && playerUIPos_[type].y < down)
	{
		temp = witch;
		Sound::getInstance().SE_play("DECISION_SE");
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
			strcpy(name, "åïém");
			break;
		case shield:
			strcpy(name, "èÇém");
			break;
		case bomber:
			strcpy(name, "îöíeém");
			break;
		case witch:
			strcpy(name, "ñÇì±ém");
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

float CharactorSelection_Scene::HandAnimation(float size)
{
	static float scale = size;
	static bool big = true;
	float mag = 0.002;
	float maxScale = 1.05;
	float minScale = 0.95;

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
		scale += mag;
	}
	else
	{
		scale -= mag;
	}

	return scale;
}

D3DXVECTOR2 CharactorSelection_Scene::StartAnimation(D3DXVECTOR2 pos)
{
	D3DXVECTOR2 tempPos = pos;
	float speed = 200.0;

	if (tempPos.x > 0)
	{
		tempPos.x -= speed;
	}
	return tempPos;
}

void CharactorSelection_Scene::MeshRender(jobName name, int type)
{

	D3DXVECTOR3 pos(meshPos_[type].x, meshPos_[type].y, meshPos_[type].z);
	//D3DXVECTOR3 posD(-3.5, 0, 0);
	//D3DXVECTOR3 posD(-1.2, 0, 0);
	float scale = 0.11;
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


void CharactorSelection_Scene::ChoiceJobUIRender(jobName name, int type)
{
	if (name == not)
	{
		return;
	}

	float middleSpace = 470;
	float posY = 690;
	float space = 93.75;
	float posX = 70 + name*middleSpace + type*space;
	float scale = 0.6;
	switch (type)
	{
	case Player1:
		charaSelect_UI["player1"]->Render(D3DXVECTOR2(posX, posY), D3DXVECTOR2(scale, scale), true);
		break;
	case Player2:
		charaSelect_UI["player2"]->Render(D3DXVECTOR2(posX, posY), D3DXVECTOR2(scale, scale), true);
		break;
	case Player3:
		charaSelect_UI["player3"]->Render(D3DXVECTOR2(posX, posY), D3DXVECTOR2(scale, scale), true);
		break;
	case Player4:
		charaSelect_UI["player4"]->Render(D3DXVECTOR2(posX, posY), D3DXVECTOR2(scale, scale), true);
		break;
	default:
		break;
	}

}

void CharactorSelection_Scene::Render()
{

	static float fingerUIScale = 1.0f;
	fingerUIScale = HandAnimation(fingerUIScale);
	charaSelect_UI["player1"]->Render(playerUIPos_[Player1], D3DXVECTOR2(fingerUIScale, fingerUIScale), true);
	charaSelect_UI["player2"]->Render(playerUIPos_[Player2], D3DXVECTOR2(fingerUIScale, fingerUIScale), true);
	charaSelect_UI["player3"]->Render(playerUIPos_[Player3], D3DXVECTOR2(fingerUIScale, fingerUIScale), true);
	charaSelect_UI["player4"]->Render(playerUIPos_[Player4], D3DXVECTOR2(fingerUIScale, fingerUIScale), true);

	D3DXVECTOR2 pos(1640, 670);
	if (nextFlg_)
	{
		charaSelect_UI["decideButton"]->Render(pos, D3DXVECTOR2(1, 1), true);
	}
	else
	{
		charaSelect_UI["beforeButton"]->Render(pos, D3DXVECTOR2(1, 1), true);
	}

	charaSelect_UI["CHARASELECT_UI"]->Render(D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1), false);

	for (int i = 0; i < 4; i++)
	{
		MeshRender(choiceJob_[i], i);
	}

	//ÉÇÅ[ÉVÉáÉì
	float speed = 1.0f / 40.0f;
	sword_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	shield_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	bomber_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	witch_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);

	camera_->Render();
}

