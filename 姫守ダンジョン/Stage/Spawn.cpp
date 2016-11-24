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
void Spawn::SpawnInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* name)
{
	hWnd_ = m_hWnd;
	pDevice_ = m_pDevice;
	pDeviceContext_ = m_pDeviceContext;

	char FileName[80];
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Stage/");
	strcat_s(FileName, sizeof(FileName), name);
	if (Init(m_hWnd, m_pDevice, m_pDeviceContext, FileName))
	{
		return;
	}

	m_vPos = { 0,0,0 };
	spawnID_ = 0;
	amount_ = 5;
	memset(enemyName_, 0, sizeof(enemyName_));
	strcpy_s(enemyName_, sizeof(enemyName_), "t01.X");

}

//
//	@brief	エネミーリストのセット
void Spawn::ListSet(ParameterRead* param, CharactorManager* target)
{
	srand((unsigned)time(NULL));
	int range = 5;
	for (int i = 0; i < amount_; i++)
	{
		EnemyJobManager* enemy = new Slim;
		enemy->CharaInit(hWnd_, pDevice_, pDeviceContext_, enemyName_);
		enemy->SetParameter(param->GetEnemyParamList("スライム"));
		enemy->SetTarget(target);
		enemy->m_Pos = D3DXVECTOR3(rand() % range + m_vPos.x, 0, rand() % range +m_vPos.z);
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
void Spawn::SpawnRender(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	Render(mView, mProj, D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1));
}