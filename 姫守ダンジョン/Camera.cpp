//
//	@file	Camera.cpp
//	@brief	カメラ関連
//	@date	2016/11/08
//	@author	仁科香苗

#include "Camera.h"

D3DXMATRIX Camera::mView_;
D3DXMATRIX Camera::mProj_;
//D3DXVECTOR3 Camera::movePow_;
//D3DXVECTOR3 Camera::gazePoint_;

//
//	@brief	コンストラクタ
Camera::Camera()
{

	zoom = 6;
	farPlayerPos_ = movePow_;
	//dist_ = zoom;
	dist_ = 0;
	temp_ = 27;
}

//
//	@brief	デストラクタ
Camera::~Camera()
{
}

//
//	@brief	プレイヤーポジションセット	
void Camera::SetPlayerPos(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 pPos = pos;
	float distx = powf(pos.x - gazePoint_.x, 2) + powf(pos.z - gazePoint_.z, 2);

	if (dist_ <= distx)
	{
		farPlayerPos_ = pos;
		dist_ = distx;
		//temp_ = dist_;
	}
}

//
//	@brief	メインシーンゲーム開始時更新
bool Camera::Main_Start_FirstUpdate()
{
	//movePow_ = D3DXVECTOR3(0, 45, -45);
	static bool nextMoveFlg = false;
	float speed = 0.05;
	//if (!nextMoveFlg)
	//{
	gazePoint_ = D3DXVECTOR3(movePow_.x, movePow_.y, movePow_.z + 1.0f);
	if (movePow_.x < 3.0f)
	{
		movePow_.x += speed;
	}
	else
	{
		return true;
	}
	//}
	//else
	//{
	//	D3DXVECTOR3 firstMovePos(0, 45, -45);
	//	D3DXVECTOR3 firstGazePos(0, 0, -12);
	//	speed = 0.4;
	//	//カメラ座標移動
	//	//x軸移動
	//	if (movePow_.x > firstMovePos.x)
	//	{
	//		movePow_.x -= speed;
	//	}
	//	//y軸移動
	//	if (movePow_.y < firstMovePos.y)
	//	{
	//		movePow_.y += speed;
	//	}
	//	//z軸移動
	//	if (movePow_.z > firstMovePos.z)
	//	{
	//		movePow_.z -= speed;
	//	}
	//	//gazePoint_ = firstGazePos;
	//	//注視点座標移動
	//	//x軸移動
	//	speed = 0.1;
	//	if (gazePoint_.x > firstGazePos.x)
	//	{
	//		gazePoint_.x -= speed;
	//	}
	//	//y軸移動
	//	if (gazePoint_.y > firstGazePos.y)
	//	{
	//		gazePoint_.y -= speed;
	//	}
	//	//z軸移動
	//	if (gazePoint_.z > firstGazePos.z)
	//	{
	//		gazePoint_.z -= speed;
	//	}
	//}

	return false;
}

bool Camera::Main_Start_SecondUpdate()
{
	D3DXVECTOR3 firstMovePos(0, 40, -40);
	D3DXVECTOR3 firstGazePos(0, 0, -12);
	float speed = 0.4;
	D3DXVECTOR3 tempPos = movePow_;
	D3DXVECTOR3 tempGaze = gazePoint_;
	//カメラ座標移動
	//x軸移動
	if (movePow_.x > firstMovePos.x)
	{
		movePow_.x -= speed;
	}
	//y軸移動
	if (movePow_.y < firstMovePos.y)
	{
		movePow_.y += speed;
	}
	//z軸移動
	if (movePow_.z > firstMovePos.z)
	{
		movePow_.z -= speed;
	}
	//gazePoint_ = firstGazePos;
	//注視点座標移動
	//x軸移動
	speed = 0.1;
	if (gazePoint_.x > firstGazePos.x)
	{
		gazePoint_.x -= speed;
	}
	//y軸移動
	if (gazePoint_.y > firstGazePos.y)
	{
		gazePoint_.y -= speed;
	}
	//z軸移動
	if (gazePoint_.z > firstGazePos.z)
	{
		gazePoint_.z -= speed;
	}

	if (tempPos == movePow_ && tempGaze == gazePoint_)
	{
		movePow_ = firstMovePos;
		gazePoint_ = firstGazePos;
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
	movePow_.z = gazePoint_.z - 40;
	float y = x - movePow_.x;
	movePow_.y += y;
	x = movePow_.x;
}

void Camera::TitleUpdate(float radius)
{
	//static float move = 0;
	//movePow_.x += cosf(move);
	//movePow_.z += sinf(move);
	//move += 0.01;
	static float degree = -100;
	float radian = D3DX_PI / 180 * degree;
	movePow_.x = gazePoint_.x + radius*cosf(radian);
	movePow_.z = gazePoint_.z + radius*sinf(radian);
	degree += 0.1f;
}

//	@brief			描画
//	@param (mView)	描画用マトリックス
//	@param (mProj)	射影変換用マトリックス
void Camera::Render()
{
	//ビュートランスフォーム カメラをキャラの後ろに配置するだけ
	D3DXVECTOR3 camPos = movePow_;
	D3DXVECTOR3 lookPos = gazePoint_;
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//上方位置

	D3DXMatrixTranslation(&tran_, 0, 0, 0);
	D3DXMatrixRotationY(&yaw_, 0);
	//D3DXMatrixRotationZ(&pitch_, gazePoint_.z);
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