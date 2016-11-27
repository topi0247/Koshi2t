#include "./Princess.h"

//
//	@brief	コンストラクタ
Princess::Princess()
{
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
	}
	else
	{
		m_Dir = D3DXVECTOR3(0, 0, 0);
	}
}

//
//	@brief	モーション更新
void Princess::Motion_Update()
{

}

//
//	@brief	ダメージ計算
//	@note	姫の場合は死亡
void Princess::DamageCalc(unsigned int atk)
{
	aliveFlg_ = false;
}

//
//	@brief	目的地セット
void Princess::SetDestination(D3DXVECTOR3 pos)
{
	destination_ = pos;
}

//
//	@brief	封印
void Princess::Seal()
{

}

//
//	@brief	蘇生
void Princess::Resuscitation()
{
	float resDist = 3;
	std::list<CharactorManager*> resList;
	if (!deadCharaList_.empty())
	{
		for (auto c : deadCharaList_)
		{
			if (collision_->CharaNear(m_Pos, c->m_Pos, resDist))
			{
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
}