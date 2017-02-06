//
//	@file	Camera.cpp
//	@brief	カメラ関連
//	@date	2016/11/08
//	@author	仁科香苗

#include "Camera.h"

D3DXMATRIX Camera::mView_;
D3DXMATRIX Camera::mProj_;

//
//	@brief	コンストラクタ
Camera::Camera()
	:titleCmeraSpeed_(0.1)
	, mainCameraSpeedF_(0.05)
	, mainCameraSpeedS_(0.4)
	, zoom_(6)
{
	firstMovePos_ =D3DXVECTOR3(0, 33.6, -41.53);
	firstGazePos_ =D3DXVECTOR3(0, 0, -12);
	mainDist_ = 20;
}

//
//	@brief	デストラクタ
Camera::~Camera()
{
}

//
//	@brief	メインゲーム開始時直後更新
bool Camera::Main_Start_FirstUpdate()
{
	static bool nextMoveFlg = false;
	float speed = mainCameraSpeedF_;
	gazePoint_ = D3DXVECTOR3(movePow_.x, movePow_.y, movePow_.z + 1.0f);
	if (movePow_.x < 3.0f)
	{
		movePow_.x += speed;
	}
	else
	{
		return true;
	}

	return false;
}

//
//	@brief	メインゲーム開始更新
bool Camera::Main_Start_SecondUpdate()
{
	float speed = mainCameraSpeedS_;
	D3DXVECTOR3 tempPos = movePow_;
	D3DXVECTOR3 tempGaze = gazePoint_;
	//カメラ座標移動
	//x軸移動
	if (movePow_.x > firstMovePos_.x)
	{
		movePow_.x -= speed;
	}
	//y軸移動
	if (movePow_.y < firstMovePos_.y)
	{
		movePow_.y += speed;
	}
	//z軸移動
	if (movePow_.z > firstMovePos_.z)
	{
		movePow_.z -= speed;
	}
	gazePoint_ = firstGazePos_;
	if (tempPos == movePow_)
	{
		movePow_ = firstMovePos_;
		return true;
	}

	return false;
}

//
//	@brief	メインシーンゲーム中更新
void Camera::Main_Game_Update()
{
	static float x = movePow_.x;
	movePow_.x = gazePoint_.x;
	movePow_.z = gazePoint_.z - mainDist_;
	x = movePow_.x;
}

//
//	@brief			タイトル更新
//	@param(radius)	回転角度
void Camera::TitleUpdate(float radius)
{
	static float degree = -100;
	float radian = D3DX_PI / 180 * degree;
	movePow_.x = gazePoint_.x + radius*cosf(radian);
	movePow_.z = gazePoint_.z + radius*sinf(radian);
	degree += titleCmeraSpeed_;
}

//	@brief			描画
//	@param (mView)	描画用マトリックス
//	@param (mProj)	射影変換用マトリックス
void Camera::Render()
{
	//ビュートランスフォーム
	D3DXVECTOR3 camPos = movePow_;
	D3DXVECTOR3 lookPos = gazePoint_;
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//上方位置

	D3DXMatrixTranslation(&tran_, 0, 0, 0);
	D3DXMatrixRotationY(&yaw_, 0);
	oriMat_ = yaw_*tran_;

	D3DXVec3TransformCoord(&camPos, &camPos, &oriMat_);
	D3DXVec3TransformCoord(&lookPos, &lookPos, &oriMat_);

	D3DXMatrixLookAtLH(&mView_, &camPos, &lookPos, &vUpVec);

	// プロジェクショントランスフォーム（射影変換）
	D3DXMatrixPerspectiveFovLH(&mProj_, D3DX_PI / zoom_, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);
}

//
//	@brief	デバッグ用カメラ移動	
void Camera::DebugMove()
{
	static float Yaw = 0, Roll = -23;
	Yaw += -(GetKeyState(VK_LEFT) & 0x80)*0.0005 + (GetKeyState(VK_RIGHT) & 0x80)*0.0005;
	Roll += -(GetKeyState(VK_DOWN) & 0x80)*0.001 + (GetKeyState(VK_UP) & 0x80)*0.001;
	D3DXMatrixRotationY(&yaw_, Yaw);
	gazePoint_ = D3DXVECTOR3(0, Roll, 10);
	D3DXVec3TransformCoord(&gazePoint_, &gazePoint_, &yaw_);

	movePow_.x += -(GetKeyState('A') & 0x80)*0.001 + (GetKeyState('D') & 0x80)*0.001;
	movePow_.y += -(GetKeyState('Q') & 0x80)*0.001 + (GetKeyState('E') & 0x80)*0.001;
	movePow_.z += -(GetKeyState('S') & 0x80)*0.001 + (GetKeyState('W') & 0x80)*0.001;

	//リセット
#if _DEBUG
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		movePow_ = D3DXVECTOR3(0, 0, 0); /*D3DXVECTOR3(0, 48, -40);*/
		Yaw = 0;
		Roll = -11;
	}
#endif

}