//
//	@file	CharactorManager.h
//	@brief	キャラクター管理クラス
//	@date	2016/11/09
//	@outher	仁科香苗

#include "./CharactorManager.h"

//
//	@brief	コンストラクタ
CharactorManager::CharactorManager()
	:opponentWeight_(1)
	, aroundCharaList_(0)
	, knockBackFlg_(0)
	, knockBackPos_(0, 0, 0)
	, knockBackDis_(0)
{
	collision_ = new Collision;
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	//opponentWeight_ = 1;
}

//
//	@brief	デストラクタ
CharactorManager::~CharactorManager()
{
	delete collision_;
	collision_ = nullptr;
}


//
//	@brief				ノックバック処理
//	@param (atkPos)		攻撃が当たった地点の座標
//	@param (distance)	ノックバックする距離
void CharactorManager::KnockBack(D3DXVECTOR3 atkPos, float distance)
{
	//方向取得
	D3DXVECTOR3 dir = m_Pos - atkPos;

	//正規化
	D3DXVec3Normalize(&dir, &dir);

	//角度を算出
	float angle = (atan2(dir.z, dir.x)*-1) - (D3DX_PI / 2.0f);

	//ノックバックスピード
	const float knockBackSpeed = 1.0f;

	m_Dir = D3DXVECTOR3(knockBackSpeed*dir.x, 0, knockBackSpeed*dir.z);

	m_Pos += m_Dir;

	if (!collision_->CharaNear(m_Pos, atkPos, distance))
	{
		knockBackFlg_ = false;
	}
}

//
//	@brief			キャラの回転処理
//	@param (dieVec)	回転の向き
void CharactorManager::Rotation(D3DXVECTOR3 dirVec)
{
	//角度を算出
	float angel = (atan2(dirVec.z, dirVec.x)*-1) - (D3DX_PI / 2.0f);

	m_Yaw = angel;
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
//	@brief			ノックバック
//	@param (pos)	攻撃者の座標
//	@param (dist)	ノックバック距離
void CharactorManager::SetKnockBack(D3DXVECTOR3 pos, float dist)
{
	knockBackFlg_ = true;
	knockBackPos_ = pos;
	knockBackDis_ = dist;
}

//
//	@brief	移動の更新
void CharactorManager::Move_Update()
{
	if (aliveFlg_ == true)
	{
		if (knockBackFlg_ == false && moveAbleFlg_ == true)
		{
			m_Pos += m_Dir;
		}
		else if (knockBackFlg_ == true)
		{
			KnockBack(knockBackPos_, knockBackDis_);
		}
	}
}

//
//	@brief				周辺にいるキャラクターをリストに追加
//	@param (charactor)	周辺にいるキャラクター
void CharactorManager::SetAroundChara(CharactorManager* charactor)
{
	for (auto list : aroundCharaList_)
	{
		if (list == charactor)
		{
			return;
		}
	}

	aroundCharaList_.push_back(charactor);
}

//
//	@brief	周辺にいるキャラクターがまだ周辺にいるかどうかのチェック
void CharactorManager::AroundCharaCheck()
{
	float dist = 10;
	int count = 0;

	for (size_t i = 0; i < aroundCharaList_.size(); i++)
	{
		//for (auto list : aroundCharaList_)
		//{
		if (!collision_->CharaNear(m_Pos, aroundCharaList_[count]->m_Pos, dist))
		{
			//いなかったら削除
			aroundCharaList_.erase(aroundCharaList_.begin() + count);
			--count;

		}

		/*if (aroundCharaList_.empty())
		{
			break;
		}*/
		++count;
		//}
	}
}

//
//	@brief	移動方向にキャラクターがいるか
//	@note	移動方向にキャラクターがいたら、そのキャラクターの重さを取得
void CharactorManager::MoveCharaHit()
{
	float dist = 2;
	float degree = D3DXToDegree(m_Yaw);
	CharactorManager* opp = nullptr;
	for (auto c : aroundCharaList_)
	{
		if (collision_->CharaNear(m_Pos, c->m_Pos, dist))
		{
			D3DXVECTOR3 vec = c->m_Pos - m_Pos;
			float angle = (atan2(vec.z, vec.x)*-1) - (D3DX_PI / 2.0f);
			angle = D3DXToDegree(angle);

			float hitAngle = 90 / 2;
			if (fabsf(degree - angle) <= hitAngle)
			{
				/*opponentWeight_ = c->ownWright_;*/
				opponentWeight_ = 0;
				opp = c;
			}
		}
	}
	if (opp == nullptr)
	{
		opponentWeight_ = 1;
	}
}

//
//	@brief	進行方向にいるキャラクターの重さセット
void CharactorManager::SetOppWeight(float weight)
{
	opponentWeight_ = weight;
}

//
//	@brief	キャラクタータイプ取得
CharaType CharactorManager::GetCharaType()const
{
	return charaType_;
}

//
//	@brief	全キャラクターセット
void CharactorManager::SetAllCharaList(std::vector<CharactorManager*> list)
{
	allCharaList_ = list;
}

//
//	@brief			描画
//	@param (mView)	描画用マトリックス
//	@param (mProj)	射影変換用マトリックス
void CharactorManager::CharaRender(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	m_View = mView;
	m_Proj = mProj;
	Render();
}
