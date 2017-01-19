#pragma once
#include "./../../Origin.h"
#include "./../../Camera.h"
#include "./../../Effekseer/Effect.h"
#include "./../../Sound/Sound.h"
#include "./../../DebugDraw/D3D11_TEXT.h"
#include "./../../Charactor/Player/GamePad.h"
#include "./../../UI/TD_Graphics.h"

class SceneBase
{
public:
	virtual ~SceneBase() {};
	virtual SceneBase* Update(SceneBase* scene) = 0;	//XVˆ—
	virtual void Render() = 0;		//•`‰æ
	virtual void Init() = 0;		//‰Šú‰»
	virtual void Destroy() = 0;		//I—¹ˆ—
};

