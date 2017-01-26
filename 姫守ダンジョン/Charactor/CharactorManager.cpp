//
//	@file	CharactorManager.h
//	@brief	キャラクター管理クラス
//	@date	2016/11/09
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#include "./CharactorManager.h"

std::vector<CharactorManager*> CharactorManager::allCharaList_;

//
//	@brief	コンストラクタ
CharactorManager::CharactorManager()
	:opponentWeight_(1)
	, aroundCharaList_(0)
	, knockBackFlg_(0)
	, knockBackPos_(0, 0, 0)
	, knockBackDis_(0)
	, motionNo_(0)
	, motionSpeed_(0.01)
	, motionCount_(0)
	, motionFrame_(0)
	, damageCount_(0)
{
	collision_ = new Collision;
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	motionChange_ = true;
	perpetrator_ = Non;
	damageFlg_ = false;
	creator_ = new CharactorCreator;
	//opponentWeight_ = 1;
}

//
//	@brief	デストラクタ
CharactorManager::~CharactorManager()
{
	if (mesh_ != NULL)
	{
		SAFE_DELETE(mesh_);
	}
	delete creator_;
	creator_ = nullptr;
	delete collision_;
	collision_ = nullptr;
}

//
//	@brief モデル読み込み・初期化
void CharactorManager::CharaInit(char* name)
{
	mesh_ = new CD3DXSKINMESH;
	if (charaType_ != Enemy)
	{
		mesh_ = creator_->LoadChara(name);
	}
	//XFileRead* xfileRead = new XFileRead;
	MotionRead* motionRead = new MotionRead;
	//XFile* xfile = xfileRead->GetXFile(name);
	//CreateFromX(xfile->GetFilePath());
	SetMotionData(motionRead->GetMotionUser(name));
	SetParameter(name);
}

//
//	@brief	解放
void CharactorManager::Destroy()
{
	if (mesh_)
	{
		SAFE_DELETE(mesh_);
	}
}

//
//	@brief	モーションデータセット
void CharactorManager::SetMotionData(Motion* motionData)
{
	motion_ = motionData;
}

//
//	@brief				ノックバック処理
//	@param (atkPos)		攻撃が当たった地点の座標
//	@param (distance)	ノックバックする距離
void CharactorManager::KnockBack(D3DXVECTOR3 atkPos, float distance, float speed)
{
	//方向取得
	D3DXVECTOR3 dir = m_Pos - atkPos;

	//正規化
	D3DXVec3Normalize(&dir, &dir);

	//角度を算出
	float angle = (atan2(dir.z, dir.x)*-1) - (D3DX_PI / 2.0f);

	//ノックバックスピード
	const float knockBackSpeed = speed;

	m_Dir = D3DXVECTOR3(knockBackSpeed*dir.x, 0, knockBackSpeed*dir.z);

	//m_Pos += m_Dir;

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
	D3DXVECTOR3 pos = m_Pos + slipVec;
	int no = collision_->SetSpaceNo(pos, 1);
	for (auto c : aroundCharaList_)
	{

		int cNo = collision_->SetSpaceNo(c->m_Pos, 1);
		if (cNo == no)
		{
			return;
		}
	}

	m_Dir = slipVec;

}

//
//	@brief	静止用
void CharactorManager::StopMove()
{
	m_Dir = D3DXVECTOR3(0, 0, 0);
}

//
//	@brief				ノックバック
//	@param (pos)		攻撃者の座標
//	@param (dist)		ノックバック距離
//	@param (speed)		ノックバックスピード
//	@param (charatype)	攻撃者
void CharactorManager::SetKnockBack(D3DXVECTOR3 pos, float dist, float speed, CharaType charatype)
{
	knockBackFlg_ = true;
	knockBackPos_ = pos;
	knockBackDis_ = dist;
	knockBackSpeed_ = speed;
	perpetrator_ = charatype;
}

//
//	@brief	移動の更新
void CharactorManager::Move_Update()
{
	if (aliveFlg_ == true && moveAbleFlg_ == true)
	{
		m_Pos += m_Dir;
		/*if (knockBackFlg_ == false && moveAbleFlg_ == true)
		{
			m_Pos += m_Dir;

		}
		else if (knockBackFlg_ == true)
		{
			KnockBack(knockBackPos_, knockBackDis_, knockBackSpeed_);
		}*/
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
	std::vector<CharactorManager*> delList;

	for (auto c : aroundCharaList_)
	{
		if (!(collision_->CheckSpaceNo(spaceNo_, c->spaceNo_,1,2) && c->GetAliveFlg()))
		{
			delList.push_back(c);
		}
	}

	for (auto c : delList)
	{
		auto el = std::find(aroundCharaList_.begin(), aroundCharaList_.end(), c);
		aroundCharaList_.erase(el);
	}
}

//
//	@brief	移動方向にキャラクターがいるか
void CharactorManager::MoveCharaHit()
{
	float dist = -1;
	//float degree = D3DXToDegree(m_Yaw);
	D3DXVECTOR3 pos(sinf(m_Yaw)*dist, 0, cosf(m_Yaw) * dist);
	pos += m_Pos;
	int no = collision_->SetSpaceNo(pos, 1);
	//CharactorManager* opp = nullptr;
	/*if (collision_->GetStageSpace(no) == Not)
	{
		opponentWeight_ = 1;
	}*/
	for (auto c : aroundCharaList_)
	{
		int cNo = collision_->SetSpaceNo(c->m_Pos, 1);
		if (cNo == no)
		{
			opponentWeight_ = 0;
			return;
		}
		//if (collision_->CharaNear(m_Pos, c->m_Pos, dist))
		//{
		//	D3DXVECTOR3 vec = c->m_Pos - m_Pos;
		//	float angle = (atan2(vec.z, vec.x)*-1) - (D3DX_PI / 2.0f);
		//	angle = D3DXToDegree(angle);
		//	float hitAngle = 90 / 2;
		//	if (fabsf(degree - angle) <= hitAngle)
		//	{
		//		/*opponentWeight_ = c->ownWeight_;*/
		//		opponentWeight_ = 0;
		//		opp = c;
		//	}
		//}
	}
	opponentWeight_ = 1;
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
//	@brief			モーション変更
//	@param (motion)	モーション情報
//	@param (name)	モーション名
void CharactorManager::ChangeMotion(Motion* motion, char* name)
{
	/*motionNo_ = motion->GetMotion(name)->id_;
	mesh_->m_pD3dxMesh->ChangeAnimSet(motionNo_);
	motionFrame_ = motion->GetMotion(name)->frame_;
	motionFrame_ *= 0.5f;
	motionSpeed_ = 1 / (float)motionFrame_;
	motionSpeed_ *= 0.5f;
	motionCount_ = 0;*/
	motionNo_ = motion->GetMotion(name)->id_;
	mesh_->m_pD3dxMesh->ChangeAnimSet(motionNo_);
	motionFrame_ = motion->GetMotion(name)->frame_;
	motionSpeed_ = 1 / (float)motionFrame_;
	motionCount_ = 0;
}

//
//	@brief	空間番号の取得
int CharactorManager::GetSpaceNo()
{
	return spaceNo_;
}

//
//	@brief			描画
void CharactorManager::CharaRender()
{
	bool drawFlg = true;
	mesh_->m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);

	if (damageFlg_)
	{
		if (++damageCount_ % 5 == 0)
		{
			drawFlg = false;
		}
	}

	if (drawFlg)
	{
		float scale = 0.2f;
		mesh_->Render(m_Pos, m_Yaw, D3DXVECTOR3(scale, scale, scale));
	}
}
