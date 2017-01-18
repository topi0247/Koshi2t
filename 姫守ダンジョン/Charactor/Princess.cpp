//
//	@file	Princess.h
//	@brief	姫クラス
//	@date	2016/12/01
//	@author	仁科香苗
//	@author	吉越大騎(サウンド)

#include "./Princess.h"

//
//	@brief	コンストラクタ
Princess::Princess()
{
	sealFlg_ = false;
	resFlg_ = false;
	sealSpawn_ = nullptr;
	charaType_ = PrincessT;
}

//
//	@brief	デストラクタ
Princess::~Princess()
{
}

void Princess::SetParameter(char* name)
{
	ParameterRead* parameter = new ParameterRead;
	parameter->SetPricessParameter();
}

//
//	@brief	リセット
void Princess::Reset()
{
	motionCount_ = 0;
	motionChange_ = true;
	opponentWeight_ = 1;
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	sealFlg_ = false;
	resFlg_ = false;
	aroundCharaList_.clear();
	allCharaList_.clear();
	deadCharaList_.clear();
	m_Pos = D3DXVECTOR3(0, 0, -12);
	destination_ = m_Pos;
	sealSpawn_ = nullptr;
	spawnPosList_.clear();
}

//
//	@brief	移動
void Princess::Move(float speed)
{
	if (knockBackFlg_ == true)
	{
		KnockBack(knockBackPos_, knockBackDis_, knockBackSpeed_);
		return;
	}

	float dist = 1;
	//int spNo = collision_->SetSpaceNo(destination_);
	//if (!collision_->CheckSpaceNo(spaceNo_, spNo))
	if(!collision_->CharaNear(m_Pos,destination_,dist))
	{
		//方向ベクトル
		D3DXVECTOR3 move = { 0,0,0 };
		move.x = destination_.x - m_Pos.x;
		move.z = destination_.z - m_Pos.z;
		D3DXVec3Normalize(&move, &move);

		//回転
		Rotation(move);

		//向いている方向から角度を取得
		D3DXVECTOR3 vec = D3DXVECTOR3(sinf(m_Yaw)*-1, 0, cosf(m_Yaw)*-1);

		float sp = speed;
		m_Dir = D3DXVECTOR3(vec.x*sp*opponentWeight_, 0, vec.z*sp*opponentWeight_);

		if (motionChange_==true && motionNo_ != motion_->GetMotion("walk")->id_)
		{
			motionNo_ = motion_->GetMotion("walk")->id_;
			mesh_->m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("walk")->id_);
			motionSpeed_ = 1 / (float)motion_->GetMotion("walk")->frame_;
		}
	}
	else
	{
		m_Dir = D3DXVECTOR3(0, 0, 0);

		if (motionChange_ == true && motionNo_ != motion_->GetMotion("wait")->id_)
		{
			motionNo_ = motion_->GetMotion("wait")->id_;
			mesh_->m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("wait")->id_);
			motionSpeed_ = 1 / (float)motion_->GetMotion("wait")->frame_;
		}
	}
}


//
//	@brief	ダメージ計算
//	@note	姫の場合は死亡
void Princess::DamageCalc(unsigned int atk)
{
	aliveFlg_ = false;
	if (motionChange_ == true && motionNo_ != motion_->GetMotion("dead1")->id_ && motionNo_ != motion_->GetMotion("dead2")->id_)
	{
		moveAbleFlg_ = false;
		ChangeMotion(motion_, "dead1");
		motionCount_ = 0;
	}
	if (++motionCount_>motionFrame_ && motionNo_ == motion_->GetMotion("dead1")->id_)
	{
		ChangeMotion(motion_, "dead2");
		motionCount_ = 0;
		motionChange_ = true;
	}
}

//
//	@brief	目的地セット
void Princess::SetDestination(D3DXVECTOR3 pos)
{
	destination_ = pos;
}


//
//	@brief	封印するスポーンゲートの取得
void Princess::SetSpawn(std::vector<Spawn*> spawn)
{
	for (auto s : spawn)
	{
		spawnPosList_.push_back(s);
	}
}

//
//	@brief	封印
void Princess::Seal()
{
	float dist = 5;
	if (!spawnPosList_.empty())
	{
		for (auto spawn : spawnPosList_)
		{
			if (collision_->CharaNear(m_Pos, spawn->GetPos(), dist))
			{
				sealFlg_ = true;
				sealSpawn_ = spawn;
			}
		}
	}
}

//
//	@brief	封印するスポーンゲートを返す
Spawn* Princess::SealSpawn()
{

	if (sealFlg_ == true)
	{
		if (motionNo_ != motion_->GetMotion("prayer")->id_)
		{
			motionChange_ = false;
			//m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("prayer")->id_);
			//motionSpeed_ = 1 / (float)motion_->GetMotion("prayer")->frame_;
			ChangeMotion(motion_, "prayer");
		}

		if (++motionCount_>motion_->GetMotion("prayer")->frame_)
		{
			sealFlg_ = false;
			motionCount_ = 0;
			motionChange_ = true;
			//ChangeMotion(motion_, "wait");
			auto el = std::find(spawnPosList_.begin(), spawnPosList_.end(), sealSpawn_);
			spawnPosList_.erase(el);
			return sealSpawn_;
		}
	}
	return nullptr;
}

//
//	@brief	蘇生
void Princess::Resuscitation()
{
	//float resDist = 100;
	std::list<CharactorManager*> resList;
	if (!deadCharaList_.empty())
	{
		for (auto c : deadCharaList_)
		{
			//if (collision_->CharaNear(m_Pos, c->m_Pos, resDist))
			if (collision_->CheckSpaceNo(spaceNo_, c->GetSpaceNo()))
			{

				//if(motionNo_!=motion_->GetMotion("prayer"))
				c->SetRevivalFlg();
				resList.push_back(c);
			}
		}
	}



	if (!resList.empty())
	{
		for (auto c : resList)
		{
			auto res = std::find(deadCharaList_.begin(), deadCharaList_.end(), c);
			deadCharaList_.erase(res);
		}
		resList.clear();
	}
}

//
//	@breif	死亡キャラセット
void Princess::SetDeadCharaList(PlayerManager* chara)
{
	deadCharaList_.push_back(chara);
}

//
//	@brief	更新
void Princess::CharaUpdate()
{
	//空間番号の更新
	spaceNo_ = collision_->SetSpaceNo(m_Pos);

	//移動
	float speed = 0.05;
	MoveCharaHit();
	Move(speed);

	//蘇生
	Resuscitation();

	//封印
	Seal();

	//モーションスピード
	mesh_->m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);

}