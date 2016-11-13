//
//	@file	Camera.cpp
//	@brief	カメラ関連
//	@date	2016/11/08
//	@outher	仁科香苗

#include "Camera.h"

//
//	@brief	コンストラクタ
Camera::Camera()
{
	movePow_ = D3DXVECTOR3(0, 48, -40);
	gazePoint_ = D3DXVECTOR3(0,0,0);
	zoom = 4;

}

//
//	@brief	デストラクタ
Camera::~Camera()
{
}

//
//	@brief	更新
void Camera::Update()
{
	DebugMove();
}

//
//	@brief	更新処理
//	@param (pos)	
//
//	@brief			描画
//	@param (mView)	描画用マトリックス
//	@param (mProj)	射影変換用マトリックス
void Camera::Render()
{
	// ３人称視点処理　ビュートランスフォーム カメラをキャラの後ろに配置するだけ
	D3DXVECTOR3 camPos=movePow_;
	D3DXVECTOR3 lookPos=gazePoint_;
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//上方位置

	D3DXMatrixTranslation(&tran_, 0, 0, 0);
	D3DXMatrixRotationY(&yaw_, 0);
	oriMat_ = yaw_*tran_;

	D3DXVec3TransformCoord(&camPos, &camPos, &oriMat_);
	D3DXVec3TransformCoord(&lookPos, &lookPos, &oriMat_);

	D3DXMatrixLookAtLH(&mView_, &camPos, &lookPos, &vUpVec);

	// プロジェクショントランスフォーム（射影変換）
	D3DXMatrixPerspectiveFovLH(&mProj_, D3DX_PI / zoom, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);
}

//
//	@brief	デバッグ用カメラ移動	
void Camera::DebugMove()
{
	static float Yaw = 0, Roll = -11;
	Yaw += -(GetKeyState(VK_LEFT) & 0x80)*0.00005 + (GetKeyState(VK_RIGHT) & 0x80)*0.00005;
	Roll += -(GetKeyState(VK_DOWN) & 0x80)*0.0001 + (GetKeyState(VK_UP) & 0x80)*0.0001;
	D3DXMatrixRotationY(&yaw_, Yaw);
	gazePoint_ = D3DXVECTOR3(0, Roll, 10);
	D3DXVec3TransformCoord(&gazePoint_, &gazePoint_, &yaw_);

	movePow_.x += -(GetKeyState('A') & 0x80)*0.001 + (GetKeyState('D') & 0x80)*0.001;
	movePow_.y += -(GetKeyState('Q') & 0x80)*0.001 + (GetKeyState('E') & 0x80)*0.001;
	movePow_.z += -(GetKeyState('S') & 0x80)*0.001 + (GetKeyState('W') & 0x80)*0.001;

	//リセット
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		movePow_ = D3DXVECTOR3(0, 48, -40);
		Yaw = 0;
		Roll = -11;
	}

}