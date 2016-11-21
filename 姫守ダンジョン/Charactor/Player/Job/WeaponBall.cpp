#include "./WeaponBall.h"


//
//	@brief	飛び道具コンストラクタ
WeaponBall::WeaponBall(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, D3DXVECTOR3 pos)
	:delCount_(0)
{
	weaponBall_ = new STATICMESH::CD3DXMESH;
	char FileName[80] = "./Model/XFiles/Player/scale1.x";
	if (FAILED(weaponBall_->Init(m_hWnd, m_pDevice, m_pDeviceContext, FileName)))
	{
		return;
	}
	weaponBall_->m_vPos = pos;
	weaponBall_->m_fScale = 0.5;
	startPos_ = pos;
	delFlg_ = false;
	col_ = new Collision;
}

//
//	@brief	飛び道具デストラクタ
WeaponBall::~WeaponBall()
{
	delete weaponBall_;
	weaponBall_ = nullptr;
	delete col_;
	col_ = nullptr;
}

//
//	@brief			方向セット
//	@param (dir)	方向ベクトル
void WeaponBall::SetDir(D3DXVECTOR3 dir)
{
	dir_ = dir;
}

//
//	@brief			サイズセット
//	@param (scale) 変更するサイズ
void WeaponBall::SetScale(float scale)
{
	weaponBall_->m_fScale += scale;
}

//
//	@brief			飛び道具の移動更新
//	@param (dist)	移動終了距離
void WeaponBall::Move_Weapon(float dist)
{
	float speed = 3;
	if (col_->CharaNear(startPos_, weaponBall_->m_vPos, dist))
	{
		weaponBall_->m_vPos += D3DXVECTOR3(dir_.x*speed, 0, dir_.z*speed);
	}
	else
	{
		delFlg_ = true;
	}
	
	Hit();
}

//
//	@brief	一定時間後に消える
void WeaponBall::Time_Del_Weapon(int frame)
{
	if (++delCount_ >= frame)
	{
		Hit();
		delFlg_ = true;
		delCount_ = 0;
	}
}

//
//	@brief			被弾する可能性のあるキャラクターリスト
//	@param (chara)	ダメージを食らうキャラ
void WeaponBall::SetDamageList(std::vector<CharactorManager*> chara, CharaType cType)
{
	for (auto c : chara)
	{
		if (c->GetCharaType() != cType)
		{
			if (col_->CharaNear(weaponBall_->m_vPos, c->m_Pos, range_))
			{
				damageList_.push_back(c);
			}
		}
	}
}

//
//	@brief	被弾するキャラ更新
//	@param (chara)	被弾するキャラ
void WeaponBall::SetDamageChara(CharactorManager* chara)
{
	damageList_.push_back(chara);
}

//
//	@brief 弾が消えるかどうか
bool WeaponBall::GetDelFlg()const
{
	return delFlg_;
}

//
//	@brief	座標取得
D3DXVECTOR3 WeaponBall::GetPosition()const
{
	return weaponBall_->m_vPos;
}

//
//	@brief	攻撃ヒット
void WeaponBall::Hit()
{
	if (!damageList_.empty())
	{
		for (auto c : damageList_)
		{
			if (col_->CharaNear(weaponBall_->m_vPos, c->m_Pos, range_))
			{
				c->SetKnockBack(weaponBall_->m_vPos, 10);
				delFlg_ = true;
			}
		}
	}
}

//
//	@brief			攻撃範囲の設定とノックバック距離の設定
//	@param (range)	攻撃の範囲
//	@param (dist)	ノックバックする距離
void WeaponBall::SetHitRangeKnockBackDist(float range, float dist)
{
	range_ = range;
	dist_ = dist;
}

//
//	@brief	攻撃の当たる範囲取得
float WeaponBall::GetHitRange()const
{
	return range_;
}

//
//	@brief	ノックバックする距離取得
float WeaponBall::GetKnockBackDist()const
{
	return dist_;
}

//
//	@brief	描画
void WeaponBall::Render(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	weaponBall_->Render(mView, mProj, D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1));
}