//
//	@file	Camera.h
//	@brief	カメラ関連
//	@date	2016/11/08
//	@author	仁科香苗

#pragma once
#include <math.h>
#include "./Origin.h"

class Camera
{
	D3D11_TEXT* debugText_;						//デバッグテキスト
	D3DXMATRIX oriMat_, tran_, yaw_, pitch_;	//マトリックス

	const float titleCmeraSpeed_;	//タイトルシーン回転速度
	const float mainCameraSpeedF_;	//メインシーン移動速度、開始直後
	const float mainCameraSpeedS_;	//メインシーン移動速度、開始後
	D3DXVECTOR3 firstMovePos_;		//メインシーン、ゲーム開始時の座標
	D3DXVECTOR3 firstGazePos_;		//メインシーン、ゲーム開始時の注視点
	float mainDist_;				//カメラと注視点とのZ座標の差分
	float zoom_;					//ズーム値
	void DebugMove();				//デバッグ用カメラ移動
public:
	Camera();
	~Camera();

	static D3DXMATRIX mView_;	//ビューtランスフォーム		
	static D3DXMATRIX mProj_;	//プロジェクショントランスフォーム
	D3DXVECTOR3 movePow_;		//移動量
	D3DXVECTOR3 gazePoint_;		//注視点

	void TitleUpdate(float radius);			//タイトル画面更新
	bool Main_Start_FirstUpdate();			//ゲームメイン開始直後更新
	bool Main_Start_SecondUpdate();			//ゲームメイン開始更新
	void Main_Game_Update();				//ゲームメイン中更新
	void Render();							//描画処理
	float GetZoom()const { return zoom_; };	//ズーム値取得
};

