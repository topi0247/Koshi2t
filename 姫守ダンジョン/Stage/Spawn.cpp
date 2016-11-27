#include "./Spawn.h"

//
//	@brief	コンストラクタ
Spawn::Spawn()
{
	spawnID_ = 0;
	amount_ = 10;
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

	m_vPos = { 0,0,0 };
	spawnID_ = 0;
	amount_ = 1;

	memset(enemyName_, 0, sizeof(enemyName_));
	strcpy_s(enemyName_, sizeof(enemyName_), "t01.X");

}

//
//	@brief	エネミーリストのセット
void Spawn::ListSet(ParameterRead* param, CharactorManager* target)
{
	srand((unsigned)time(NULL));
	//int range = 5;
	for (int i = 0; i < amount_; i++)
	{
		EnemyJobManager* enemy = new Slim;
		enemy->SetParameter(param->GetEnemyParamList("スライム"));
		enemy->SetTarget(target);
		enemy->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
		enemy->m_Pos = m_vPos;//D3DXVECTOR3(rand() % range + m_vPos.x, 0, rand() % range +m_vPos.z);
		insEnemyList_.push_back(enemy);
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
	Render(m_vPos,0,0.2);
}