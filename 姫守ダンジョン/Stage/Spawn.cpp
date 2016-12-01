#include "./Spawn.h"

//
//	@brief	コンストラクタ
Spawn::Spawn()
{
	spawnID_ = 0;
	m_vPos = { 0,0,0 };
}

//
//	@brief	デストラクタ
Spawn::~Spawn()
{

}

//
//	@brief	スポーンの初期化
void Spawn::SpawnInit(const char* name)
{

	char FileName[80];
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Stage/");
	strcat_s(FileName, sizeof(FileName), name);
	if (LoadXMesh(FileName))
	{
		return;
	}

	m_vPos = { 0,0,5 };
	spawnID_ = 0;
	amount_ = 5;


}

//
//	@brief	エネミーリストのセット
void Spawn::ListSet(ParameterRead* param, CharactorManager* target)
{
	srand((unsigned)time(NULL));
	int range = 10;
	for (int i = 0; i < amount_; i++)
	{
		EnemyJobManager* enemy = new Slim;
		enemy->SetParameter(param->GetEnemyParamList("スライム"));
		enemy->SetTarget(target);
		enemy->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
		enemy->m_Pos = D3DXVECTOR3(rand() % range + (m_vPos.x-range/2), 0, rand() % range +(m_vPos.z-range/2));
		insEnemyList_.push_back(enemy);
		//SAFE_DELETE(enemy);
	}
}

//
//	@brief	エネミーのスポーン
std::vector<EnemyJobManager*> Spawn::EnemySpawn()
{
	return insEnemyList_;
}

//
//	@brief	エネミーリストのリセット
void Spawn::ListReset()
{
	insEnemyList_.clear();
}

//
//	@brief	描画
void Spawn::SpawnRender()
{
	Render(m_vPos,D3DXVECTOR3(0,0,0),0.2);
}