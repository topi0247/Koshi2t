//
//	@file	Camera.h
//	@brief	ƒJƒƒ‰ŠÖ˜A
//	@date	2016/11/08
//	@outher	m‰È•c
//	@note	–¢À‘•(2016/11/08)
#pragma once
#include "./Origin.h"

class Camera
{

public:
	Camera();
	~Camera();
	void Render(D3DXMATRIX mView,D3DXMATRIX mProj);	//•`‰æˆ—
};

