#include "./CharactorSelection_Scene.h"


CharactorSelection_Scene::CharactorSelection_Scene()
{
	charaSelect_UI["CHARASELECT_UI"] = new TD_Graphics;
	//charaSelect_UI["FINGER_UI"] = new TD_Graphics;
	charaSelect_UI["player1"] = new TD_Graphics;
	charaSelect_UI["player2"] = new TD_Graphics;
	charaSelect_UI["player3"] = new TD_Graphics;
	charaSelect_UI["player4"] = new TD_Graphics;
	charaSelect_UI["Start_UI"] = new TD_Graphics;
	camera_ = new Camera;
	text_ = new D3D11_TEXT;
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
	charaSelect_UI["player1"] = nullptr;
	delete charaSelect_UI["player3"];
	charaSelect_UI["player1"] = nullptr;
	delete charaSelect_UI["player4"];
	charaSelect_UI["player1"] = nullptr;
	delete charaSelect_UI["Start_UI"];
	charaSelect_UI["Start_UI"] = nullptr;
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
	creator_ = new CharactorCreator;
	
	sword_ = creator_->LoadChara("Œ•Žm");
	shield_ = creator_->LoadChara("‚Žm");
	bomber_ = creator_->LoadChara("”š’eŽm");
	witch_ = creator_->LoadChara("–‚“±Žm");

	for (int i = 0; i < 4; i++)
	{
		choiceJob_[i] = not;
		keyWait_[i] = 0;
		pos_[i] = D3DXVECTOR2(100 + i * 500, 50);
		meshPos_[i] = D3DXVECTOR3(-3.5 + i * 2.3, 0, 0);
	}
	//meshPos_[0] = D3DXVECTOR3(-3.5, 0, 0);

	//meshPos_[0] = D3DXVECTOR3(-2.5, 0, 0);
	//meshPos_[1] = D3DXVECTOR3(-1.3, 0, 0);
	//meshPos_[2] = D3DXVECTOR3(1.5, 0, 0);
	//meshPos_[3] = D3DXVECTOR3(2, 0, 0);

	//charaSelect_UI["FINGER_UI"]->Init(L"./UI/UI_Tex/finger.png", /*0,*/ D3DXVECTOR2(0, 0), D3DXVECTOR2(115, 150), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["player1"]->Init(L"./UI/UI_Tex/finger.png", /*0,*/ D3DXVECTOR2(0, 0), D3DXVECTOR2(115, 150), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["player2"]->Init(L"./UI/UI_Tex/player_plate2.png", /*0,*/ D3DXVECTOR2(0, 0), D3DXVECTOR2(115, 150), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["player3"]->Init(L"./UI/UI_Tex/player_plate3.png", /*0,*/ D3DXVECTOR2(0, 0), D3DXVECTOR2(115, 150), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["player4"]->Init(L"./UI/UI_Tex/player_plate4.png", /*0,*/ D3DXVECTOR2(0, 0), D3DXVECTOR2(115, 150), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["CHARASELECT_UI"]->Init(L"./UI/UI_Tex/character_select.png",/* 0,*/ D3DXVECTOR2(0, 0), D3DXVECTOR2(WINDOW_WIDTH, WINDOW_HEIGHT), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	charaSelect_UI["Start_UI"]->Init(L"./UI/UI_Tex/ready.png",/* 0,*/ D3DXVECTOR2(0, 0), D3DXVECTOR2(1290, 327), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));

	camera_->gazePoint_ = D3DXVECTOR3(0, 2.4, 0);
	camera_->movePow_ = D3DXVECTOR3(0, 2.4, -10);
}

void CharactorSelection_Scene::Destroy()
{
	SAFE_DELETE(sword_);
	SAFE_DELETE(shield_);
	SAFE_DELETE(bomber_);
	SAFE_DELETE(witch_);
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
	float up = 225;
	float down = 780;
	if (pos_[type].x > 18 && pos_[type].x < 480
		&& pos_[type].y >up && pos_[type].y < down)
	{
		temp = sword;
	}
	else if (pos_[type].x > 490 && pos_[type].x < 960
		&& pos_[type].y > up && pos_[type].y < down)
	{
		temp = shield;
	}
	else if (pos_[type].x > 965 && pos_[type].x < 1430
		&& pos_[type].y > up && pos_[type].y < down)
	{
		temp = bomber;
	}
	else if (pos_[type].x > 1440 && pos_[type].x < 1900
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

float CharactorSelection_Scene::HandAnimation(float size)
{
	static float scale=size;
	static bool big = true;
	float mag = 0.001;
	float maxScale = 1.05;
	float minScale=0.95;

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
	float scale = 0.1;
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


	//D3DXVECTOR2 size(1, 1);
	//size = HandAnimation(size);
	//pos_[0].x += 0.1f;
	//static float startUIScale=1.0f;
	//startUIScale = StartAnimation(startUIScale);
	static D3DXVECTOR2 startUIPos(WINDOW_WIDTH, 400);
	if (nextFlg_)
	{
		startUIPos = StartAnimation(startUIPos);
		charaSelect_UI["Start_UI"]->Render(startUIPos, D3DXVECTOR2(1.7, 0.8), true);
	}
	else
	{
		startUIPos= D3DXVECTOR2(WINDOW_WIDTH, 400);
	}

	static float fingerUIScale = 1.0f;
	fingerUIScale = HandAnimation(fingerUIScale);
	//for (int i = 0; i < 4; i++)
	//{
		charaSelect_UI["player1"]->Render(pos_[Player1], D3DXVECTOR2(fingerUIScale,fingerUIScale), true);
		charaSelect_UI["player2"]->Render(pos_[Player2], D3DXVECTOR2(fingerUIScale, fingerUIScale), true);
		charaSelect_UI["player3"]->Render(pos_[Player3], D3DXVECTOR2(fingerUIScale, fingerUIScale), true);
		charaSelect_UI["player4"]->Render(pos_[Player4], D3DXVECTOR2(fingerUIScale, fingerUIScale), true);
	//}

	//static D3DXVECTOR2 mag(1, 1);
	//mag.x += -(GetKeyState(VK_LEFT) & 0x80)*0.001f+ (GetKeyState(VK_RIGHT) & 0x80)*0.001f;
	//mag.y += -(GetKeyState(VK_UP) & 0x80)*0.001f + (GetKeyState(VK_DOWN) & 0x80)*0.001f;


	charaSelect_UI["CHARASELECT_UI"]->Render(D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1), false);
	/*static D3DXVECTOR2 pos(0, 0); 
	float speed_= 0.01;
	pos.x += (GetKeyState(VK_RIGHT) & 0x80)*speed_ + -(GetKeyState(VK_LEFT) & 0x80)*speed_;
	pos.y += (GetKeyState(VK_DOWN) & 0x80)*speed_ + -(GetKeyState(VK_UP) & 0x80)*speed_;*/
	//if (nextFlg_)
	//{
	//	charaSelect_UI["Start_UI"]->Render(D3DXVECTOR2(360,400), D3DXVECTOR2(1, 1), true);
	//}
	//float scale = 0.15;
	//float y = 1.5;
	float speed = 1.0f / 40.0f;
	//sword_->Render(D3DXVECTOR3(-4, y, 1), 0, D3DXVECTOR3(scale, scale, scale));
	////sword_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	//shield_->Render(D3DXVECTOR3(-1, y, 1), 0, D3DXVECTOR3(scale, scale, scale));
	////shield_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	//bomber_->Render(D3DXVECTOR3(1, y, 1), 0, D3DXVECTOR3(scale, scale, scale));
	////bomber_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	//witch_->Render(D3DXVECTOR3(3.5, y, 1), 0, D3DXVECTOR3(scale, scale, scale));
	////witch_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);


	for (int i = 0; i < 4; i++)
	{
		MeshRender(choiceJob_[i], i);
	}

	//ƒ‚[ƒVƒ‡ƒ“
	sword_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	shield_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	bomber_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);
	witch_->m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);

	/*static D3DXVECTOR3 pos(0, 0, 0);
	static float scale = 0.1;
	float speedD = 0.001;
	pos.x += (GetKeyState(VK_RIGHT) & 0x80)*speedD + -(GetKeyState(VK_LEFT) & 0x80)*speedD;
	pos.y += (GetKeyState(VK_UP) & 0x80)*speedD + -(GetKeyState(VK_DOWN) & 0x80)*speedD;
	scale += (GetKeyState('L') & 0x80)*speedD + -(GetKeyState('S') & 0x80)*speedD;
	sword_->Render(pos, 0, D3DXVECTOR3(scale, scale, scale));
*/
	camera_->Render();


	////ƒfƒoƒbƒO•`‰æ
	//char str[256];
	//sprintf(str, "pos.x:%f pos.y:%f",pos.x, pos.y);
	//text_->Render(str, 0, 50);


}