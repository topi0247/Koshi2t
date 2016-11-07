//
//	@file	Camera.cpp
//	@brief	カメラ関連
//	@date	2016/11/08
//	@outher	仁科香苗
//	@note	未実装(2016/11/08)

#include "Camera.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

//
//	@brief			描画
//	@param (mView)	描画用マトリックス
//	@param (mProj)	射影変換用マトリックス
void Camera::Render(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	// ３人称視点処理　ビュートランスフォーム カメラをキャラの後ろに配置するだけ
	D3DXVECTOR3 vEyePt(0.0f, 2.0f, -4.0f); //カメラ（視点）位置
	D3DXVECTOR3 vLookatPt(0.0f, 1.7f, 0.0f);//注視位置
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//上方位置

	//視点と注視点の両方をキャラの姿勢（回転と位置）行列で曲げて移動すればいい
	D3DXMATRIX OriMat, Tran, Yaw;
	D3DXMatrixTranslation(&Tran, 0, 0, 0);
	D3DXMatrixRotationY(&Yaw, 0);
	OriMat = Yaw*Tran;

	D3DXVec3TransformCoord(&vEyePt, &vEyePt, &OriMat);
	D3DXVec3TransformCoord(&vLookatPt, &vLookatPt, &OriMat);

	D3DXMatrixLookAtLH(&mView, &vEyePt, &vLookatPt, &vUpVec);

	// プロジェクショントランスフォーム（射影変換）
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);
}