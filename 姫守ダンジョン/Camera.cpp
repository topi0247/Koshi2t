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
}

//
//	@brief	デストラクタ
Camera::~Camera()
{
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
	static D3DXVECTOR3 camPos=movePow_;
	static D3DXVECTOR3 lookPos=gazePoint_;
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//上方位置

	//視点と注視点の両方をキャラの姿勢（回転と位置）行列で曲げて移動すればいい
	
	D3DXMATRIX OriMat, Tran, Yaw;
	D3DXMatrixTranslation(&Tran, 0, 0, 0);
	D3DXMatrixRotationY(&Yaw, 0);
	OriMat = Yaw*Tran;

	D3DXVec3TransformCoord(&camPos, &camPos, &OriMat);
	D3DXVec3TransformCoord(&lookPos, &lookPos, &OriMat);

	D3DXMatrixLookAtLH(&mView_, &camPos, &lookPos, &vUpVec);

	// プロジェクショントランスフォーム（射影変換）
	D3DXMatrixPerspectiveFovLH(&mProj_, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);
}