//
//	@file	WeaponBall.cpp
//	@brief	飛び道具クラス
//	@date	2016/11/21
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#include "./WeaponBall.h"


//
//	@brief	飛び道具コンストラクタ
WeaponBall::WeaponBall()
	:delCount_(0)
{
	weaponBall_ = new CD3DXMESH;
	creator_ = new CharactorCreator;
	weaponBall_->m_fScale = 0.5;
	delFlg_ = false;
	col_ = new Collision;
	effectflg_ = false;
	//w_ball = false;
	pos_ = weaponBall_->m_vPos;
}

//
//	@brief	飛び道具デストラクタ
WeaponBall::~WeaponBall()
{
	delete weaponBall_;
	weaponBall_ = nullptr;
	delete col_;
	col_ = nullptr;
	delete creator_;
	creator_ = nullptr;
}

//
//	@brief	読み込み
void WeaponBall::Init(char* name)
{
	weaponBall_ = creator_->LoadStage(name);
	/*char FileName[80] = "./Model/XFiles/Player/";
	strcat(FileName, name);
	if (FAILED(weaponBall_->LoadXMesh(FileName)))
	{
		return;
	}*/
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
	weaponBall_->m_fScale = scale;
}

//
// @brief	初期位置
void WeaponBall::SetStartPos(D3DXVECTOR3 pos)
{
	startPos_ = pos;
	weaponBall_->m_vPos = pos;
	spaceNo_ = col_->SetSpaceNo(startPos_, 2);

	//Effect::getInstance().Update("beam2", startPos_);
	//w_ball = true;
	//Effect::getInstance().Effect_Play("magicball", weaponBall_->m_vPos);
	//Effect::getInstance().SetScale("magicball", 0.2f);
}
//
//	@brief	攻撃力セット
void WeaponBall::SetAttack(unsigned int atk)
{
	atk_ = atk;
}

//
//	@brief			飛び道具の移動更新
//	@param (dist)	移動終了距離
void WeaponBall::Move_Weapon(float speed)
{
	//int ownNo = col_->SetSpaceNo(weaponBall_->m_vPos, 1);
	//if (col_->CharaNear(startPos_, weaponBall_->m_vPos, dist))
	//{
	float fDistance = 0;
	D3DXVECTOR3 vNormal;
	if (col_->RayIntersect(weaponBall_->m_vPos, dir_, Stage::GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.3)
	{
		delFlg_ = true;
	}
	weaponBall_->m_vPos += D3DXVECTOR3(dir_.x*speed, 0, dir_.z*speed);
	//}
	//else
	//{
		//delFlg_ = true;
	//}

	spaceNo_ = col_->SetSpaceNo(weaponBall_->m_vPos, 2);

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
		effectflg_ = true;
		delCount_ = 0;
		//Effect::getInstance().Effect_Stop("magicball");
		//Effect::getInstance().Effect_Play("explosion", weaponBall_->m_vPos);
		//Effect::getInstance().SetScale("explosion", 0.8f);
	}
}

////
////	@brief			被弾する可能性のあるキャラクターリスト
////	@param (chara)	ダメージを食らうキャラ
//void WeaponBall::SetDamageList(std::vector<CharactorManager*> chara, CharaType cType,int no)
//{
//	for (auto c : chara)
//	{
//		if (c->GetCharaType() == Enemy)
//		{			
//			if (col_->CheckSpaceNo(spaceNo_, c->GetSpaceNo(), no, 2))
//			{
//				damageList_.push_back(c);
//			}
//		}
//	}
//}
//
////
////	@brief	被弾するキャラ更新
////	@param (chara)	被弾するキャラ
//void WeaponBall::SetDamageChara(CharactorManager* chara)
//{
//	damageList_.push_back(chara);
//}

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
//	@brief	スケール取得
float WeaponBall::GetScale()const
{
	return weaponBall_->m_fScale;
}

//
//	@brief	攻撃ヒット
void WeaponBall::Hit()
{
	//std::vector<CharactorManager*> hitList;
	//if (!damageList_.empty())
	//{
	for (auto c : CharactorManager::allCharaList_)
	{
		if (c->GetCharaType() != user_ && col_->CheckSpaceNo(spaceNo_, c->GetSpaceNo(), 1, 2))
		{
			damageList_.push_back(c);
		}

	}

	beforeDamageCharaList_.clear();
	if (!damageList_.empty())
	{
		for (auto d : damageList_)
		{
			if (!d->GetDamageFlg() && col_->CharaNear(weaponBall_->m_vPos, d->m_Pos, dist_))
			{
				d->SetKnockBack(weaponBall_->m_vPos, kDist_, kSpeed_, user_);
				if (hitDel_)
				{
					delFlg_ = true;
				}

				if (d->GetCharaType() == damageChara_)
				{
					d->DamageCalc(atk_);
					beforeDamageCharaList_.push_back(d);
					//敵にダメージが入った時のSE
					Sound::getInstance().SE_play(hitSoundName_);
				}
			}
		}
		damageList_.clear();
	}

}

//
//	@brief				ノックバック設定
//	@param (dist)		攻撃の範囲
//	@param (kDist)		ノックバックする距離
//	@param (kSpeed)		ノックバックスピード
//	@param (userChara)	攻撃の使用者
//	@param (damageChara)攻撃が当たるキャラクタータイプ
void WeaponBall::SetKnockBack(float dist, float kDist, float kSpeed, CharaType userChara, CharaType charatype)
{
	dist_ = dist;
	kDist_ = kDist;
	kSpeed_ = kSpeed;
	user_ = userChara;
	damageChara_ = charatype;
	beforeDamageCharaList_.clear();
}

//
//	@brief	ヒットサウンド設定
void WeaponBall::SetHitSound(std::string name)
{
	hitSoundName_ = name;
}

//
//	@brief	当たったら消えるかどうかフラグ設定
void WeaponBall::SetHitDelFlg(bool flg)
{
	hitDel_ = flg;
}

////
////	@brief	攻撃の当たる範囲取得
//float WeaponBall::GetHitDist()const
//{
//	return dist_;
//}
//
////
////	@brief	ノックバックする距離取得
//float WeaponBall::GetKnockBackDist()const
//{
//	return kDist_;
//}

//
//	@brief	描画
void WeaponBall::Render(D3DXVECTOR3 pos)
{
	weaponBall_->Render(pos, D3DXVECTOR3(0, 0, 0), weaponBall_->m_fScale);

	//if (effectflg_)
	//{
	//	Effect::getInstance().Update("explosion", weaponBall_->m_vPos);
	//	effectflg_ = false;
	//}

}