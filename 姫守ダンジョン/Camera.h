//
//	@file	Camera.h
//	@brief	カメラ関連
//	@date	2016/11/08
//	@outher	仁科香苗
#pragma once
#include "./Origin.h"

class Camera
{
	D3D11_TEXT* debugText_;

	D3DXMATRIX mView_;
	D3DXMATRIX mProj_;
	D3DXVECTOR3 movePow_;				//移動量
	D3DXVECTOR3 gazePoint_;				//注視点
	D3DXMATRIX oriMat_, tran_, yaw_,pitch_;
	float dist_,temp_;
	D3DXVECTOR3 farPlayerPos_;

	float zoom;
	float zoomPow_;
	void DebugMove();		//デバッグ用カメラ移動
public:
	Camera();
	~Camera();
	
	D3DXMATRIX GetView()const { return mView_; };
	D3DXMATRIX GetProj()const { return mProj_; };
	void Update();	//更新
	void Render();	//描画処理
	void SetPlayerPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos() { return movePow_; };
	float GetDist()const { return dist_; };
	float GetZoom()const { return zoom; };
};

