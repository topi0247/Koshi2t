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

//
//	@brief	初期化
const char* Princess::CharaInit(const char* fileName)
{
	char FileName[80] = { 0 };
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Princess/");
	strcat_s(FileName, sizeof(FileName), fileName);
	//CreateFromX(FileName);
	m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
	return FileName;
}

//
//	@brief	移動
void Princess::Move(float speed)
{
	float dist = 1;
	if (!collision_->CharaNear(m_Pos, destination_, dist))
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

		if (motionNo_ != motion_->GetMotion("walk")->id_)
		{
			motionNo_ = motion_->GetMotion("walk")->id_;
			m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("walk")->id_);
			motionSpeed_ = 1 / (float)motion_->GetMotion("walk")->frame_;
		}
	}
	else
	{
		m_Dir = D3DXVECTOR3(0, 0, 0);

		if (motionNo_ != motion_->GetMotion("wait")->id_)
		{
			motionNo_ = motion_->GetMotion("wait")->id_;
			m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("wait")->id_);
			motionSpeed_ = 1/(float)motion_->GetMotion("wait")->frame_;
		}
	}
}


//
//	@brief	ダメージ計算
//	@note	姫の場合は死亡
void Princess::DamageCalc(unsigned int atk)
{
	aliveFlg_ = false;
	if (motionNo_ != motion_->GetMotion("dead")->id_)
	{
		m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("dead")->id_);
		motionSpeed_ = 1 / (float)motion_->GetMotion("dead")->frame_;
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
void Princess::SetSpawn(Spawn* spawn)
{
	spawnPosList_.push_back(spawn);
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
			if (collision_->CharaNear(m_Pos, spawn->m_vPos, dist))
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

	if (sealFlg_ == true )
	{
		if (motionNo_ != motion_->GetMotion("prayer")->id_)
		{
			m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("prayer")->id_);
			motionSpeed_ = 1 / (float)motion_->GetMotion("prayer")->frame_;
		}

		if (++motionCount_%motion_->GetMotion("prayer")->frame_ == 0)
		{
			sealFlg_ = false;
			return sealSpawn_;
			motionCount_ = 0;
		}
	}
	return nullptr;
}

//
//	@brief	蘇生
void Princess::Resuscitation()
{
	float resDist = 100;
	std::list<CharactorManager*> resList;
	if (!deadCharaList_.empty())
	{
		for (auto c : deadCharaList_)
		{
			if (collision_->CharaNear(m_Pos, c->m_Pos, resDist))
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
	//移動
	float speed = 0.01;
	MoveCharaHit();
	Move(speed);

	//蘇生
	Resuscitation();

	//封印
	Seal();

	//モーションスピード
	m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);

}