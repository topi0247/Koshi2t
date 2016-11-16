//
//	@file	CharactorManager.h
//	@brief	キャラクター管理クラス
//	@date	2016/11/09
//	@outher	仁科香苗

#include "./CharactorManager.h"

//
//	@brief	コンストラクタ
CharactorManager::CharactorManager()
	:opponentWeight_(0)
{
}

//
//	@brief	デストラクタ
CharactorManager::~CharactorManager()
{
	
}


//
//	@brief				ノックバック処理
//	@param (atkPos)		攻撃が当たった地点の座標
//	@param (distance)	ノックバックする距離
void CharactorManager::KnockBack(D3DXVECTOR3 atkPos, float distance)
{
	//方向取得
	D3DXVECTOR3 dir = m_vPos - atkPos;

	//正規化
	D3DXVec3Normalize(&dir,&dir);

	//角度を算出
	float angle = (atan2(dir.z, dir.x)*-1) - (D3DX_PI / 2.0f);

	//ノックバックスピード
	const float knockBackSpeed = 2.0f;
}

//
//	@brief			キャラの回転処理
//	@param (dieVec)	回転の向き
void CharactorManager::Rotation(D3DXVECTOR3 dirVec)
{
	//角度を算出
	float angel = (atan2(dirVec.z, dirVec.x)*-1) - (D3DX_PI / 2.0f);
	
	m_fYaw = angel;
}

//
//	@brief	壁滑り用移動
void CharactorManager::SlipMove(D3DXVECTOR3 slipVec)
{
	m_Dir = slipVec;

}

//
//	@brief	静止用
void CharactorManager::StopMove()
{
	m_Dir = D3DXVECTOR3(0, 0, 0);
}

//
//	@brief	移動の更新
void CharactorManager::Move_Update()
{
	m_vPos += m_Dir;
}

//
//	@brief				周辺にいるキャラクターをリストに追加
//	@param (charactor)	周辺にいるキャラクター
void CharactorManager::SetAroundChara(CharactorManager* charactor)
{
	aroundCharaList_.push_back(charactor);
}

//
//	@brief	進行方向にいるキャラクターの重さセット
void CharactorManager::SetOppWeight(float weight)
{
	opponentWeight_ = weight;
}

//
//	@brief				壁にぶつかっているかどうかのフラグ更新
//	@param (wallHitFlg)	壁との衝突判定
void CharactorManager::SetHitWall(bool wallHitFlg)
{
	hitWall_ = wallHitFlg;
}

//
//	@brief			描画
//	@param (mView)	描画用マトリックス
//	@param (mProj)	射影変換用マトリックス
void CharactorManager::CharaRender(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	Render(mView, mProj, D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1));

}
