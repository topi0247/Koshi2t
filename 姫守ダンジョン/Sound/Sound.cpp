//
//	@file	Sound.cpp
//	@brief	サウンド管理クラス
//	@date	4月、1月修正
//	@author	吉越大騎
//	@note	既に用意されていたクラスを大幅に変更

#include "Sound.h"

map<string, int> SE_iSoundIndex;//SE保管庫

//=======================================================
//	コンストラクタ
//=======================================================
Sound::Sound()
{
	ZeroMemory(this, sizeof(Sound));
	bgm_flg = true;
}

//=======================================================
//	デストラクタ
//=======================================================
Sound::~Sound()
{
	for (int i = 0; i<MAX_WAV; i++)
	{
		if (m_pSourceVoice[i]) m_pSourceVoice[i]->DestroyVoice();
	}
	for (int i = 0; i<MAX_WAV; i++) SAFE_DELETE(m_pWavBuffer[i]);
	SAFE_RELEASE(m_pXAudio2);
}

//
//	@brief				BGM再生
//	@param(BGM_mode)	再生するBGM名
void Sound::BGM_play(string BGM_mode)
{
	PlaySound(SE_iSoundIndex[BGM_mode],true);
}

//
//	@brief				BGM停止
//	@param(BGM_mode)	停止するBGM名
void Sound::BGM_stop(string BGM_mode)
{
	m_pSourceVoice[SE_iSoundIndex[BGM_mode]]->Stop(0, XAUDIO2_COMMIT_NOW);
}

//
//	@brief				SE再生
//	@param(BGM_mode)	再生するSE名
void Sound::SE_play(string SE_mode)
{
	PlaySound(SE_iSoundIndex[SE_mode],false);
}

//
//	@brief				SE停止
//	@param(BGM_mode)	停止するSE名
void Sound::SE_stop(string SE_mode)
{
	m_pSourceVoice[SE_iSoundIndex[SE_mode]]->Stop(0, XAUDIO2_COMMIT_NOW);
}

void Sound::Run()
{
	//サウンド関連（XAudio2）の初期化
	InitSound();

	//BGM//
	SE_iSoundIndex["TITLE"] = LoadSound("Sound/SE/all_sound/Title.wav");
	SE_iSoundIndex["CHARACTERSELECT"] = LoadSound("Sound/SE/all_sound/select.wav");
	SE_iSoundIndex["SENTOU"] = LoadSound("Sound/SE/all_sound/game_Main.wav");
	SE_iSoundIndex["CLEAR"] = LoadSound("Sound/SE/all_sound/result.wav");
	SE_iSoundIndex["FAILED"] = LoadSound("Sound/SE/all_sound/game_Over.wav");
	
	//SE//
	SE_iSoundIndex["DECISION_SE"] = LoadSound("Sound/SE/all_sound/decision.wav");
	m_pSourceVoice[SE_iSoundIndex["DECISION_SE"]]->SetVolume(3.0f, 0);

	//============剣士============//
	//通常攻撃
	SE_iSoundIndex["S_NORMALATK"] = LoadSound("Sound/SE/sword_sound/s_normal.wav");
	m_pSourceVoice[SE_iSoundIndex["S_NORMALATK"]]->SetVolume(3.0f, 0);

	//特殊攻撃
	SE_iSoundIndex["S_SPECIAL"] = LoadSound("Sound/SE/sword_sound/s_specialATK.wav");
	m_pSourceVoice[SE_iSoundIndex["S_SPECIAL"]]->SetVolume(3.0f, 0);

	//ダメージ
	SE_iSoundIndex["S_DAMAGE"] = LoadSound("Sound/SE/sword_sound/sword_damagevoice.wav");
	m_pSourceVoice[SE_iSoundIndex["S_DAMAGE"]]->SetVolume(3.0f, 0);

	//ダメージヒット
	SE_iSoundIndex["S_DAMAGE_HIT"] = LoadSound("Sound/SE/sword_sound/sword_hit.wav");
	m_pSourceVoice[SE_iSoundIndex["S_DAMAGE_HIT"]]->SetVolume(3.0f, 0);

	//死亡
	SE_iSoundIndex["S_DEAD"] = LoadSound("Sound/SE/sword_sound/sword_dethvoice.wav");
	m_pSourceVoice[SE_iSoundIndex["S_DEAD"]]->SetVolume(3.0f, 0);

	//============盾士============//
	//通常攻撃
	SE_iSoundIndex["Sh_NORMALATK"] = LoadSound("Sound/SE/shiled_sound/shield_attack.wav");
	m_pSourceVoice[SE_iSoundIndex["Sh_NORMALATK"]]->SetVolume(2.0f, 0);

	//特殊攻撃
	SE_iSoundIndex["Sh_SPECIAL"] = LoadSound("Sound/SE/shiled_sound/shiled_SPwalk.wav");
	m_pSourceVoice[SE_iSoundIndex["Sh_SPECIAL"]]->SetVolume(5.0f, 0);

	//ダメージ
	SE_iSoundIndex["Sh_DAMAGE"] = LoadSound("Sound/SE/shiled_sound/shield_damagevoice.wav");
	m_pSourceVoice[SE_iSoundIndex["Sh_DAMAGE"]]->SetVolume(5.0f, 0);

	//ダメージヒット
	SE_iSoundIndex["Sh_DAMAGE_HIT"] = LoadSound("Sound/SE/shiled_sound/shiled_hit.wav");
	m_pSourceVoice[SE_iSoundIndex["Sh_DAMAGE_HIT"]]->SetVolume(1.0f, 0);

	//死亡
	SE_iSoundIndex["Sh_DEAD"] = LoadSound("Sound/SE/shiled_sound/shiled_dethvoice.wav");
	m_pSourceVoice[SE_iSoundIndex["Sh_DEAD"]]->SetVolume(3.0f, 0);

	//============魔導士============//
	//通常攻撃
	SE_iSoundIndex["M_NORMALATK"] = LoadSound("Sound/SE/magic_sound/magic_attack.wav");
	m_pSourceVoice[SE_iSoundIndex["M_NORMALATK"]]->SetVolume(2.0f, 0);

	//特殊攻撃
	SE_iSoundIndex["M_SPECIAL"] = LoadSound("Sound/SE/magic_sound/magic_charge.wav");
	m_pSourceVoice[SE_iSoundIndex["M_SPECIAL"]]->SetVolume(5.0f, 0);

	//ダメージ
	SE_iSoundIndex["M_DAMAGE"] = LoadSound("Sound/SE/magic_sound/magic_damagevoice.wav");
	m_pSourceVoice[SE_iSoundIndex["M_DAMAGE"]]->SetVolume(3.0f, 0);

	//ダメージヒット
	SE_iSoundIndex["M_DAMAGE_HIT"] = LoadSound("Sound/SE/magic_sound/magic_hit.wav");
	m_pSourceVoice[SE_iSoundIndex["M_DAMAGE_HIT"]]->SetVolume(3.0f, 0);

	//死亡
	SE_iSoundIndex["M_DEAD"] = LoadSound("Sound/SE/magic_sound/magic_hit.wav");
	m_pSourceVoice[SE_iSoundIndex["M_DEAD"]]->SetVolume(3.0f, 0);

	//チャージ
	SE_iSoundIndex["M_CHARGE"] = LoadSound("Sound/SE/magic_sound/m_Charge.wav");
	m_pSourceVoice[SE_iSoundIndex["M_CHARGE"]]->SetVolume(3.0f, 0);

	//============爆弾士============//
	//通常攻撃
	SE_iSoundIndex["B_NORMALATK"] = LoadSound("Sound/SE/bomb_sound/bomb_hit.wav");
	m_pSourceVoice[SE_iSoundIndex["B_NORMALATK"]]->SetVolume(2.0f, 0);

	//特殊攻撃
	SE_iSoundIndex["B_SPECIAL"] = LoadSound("Sound/SE/bomb_sound/pui.wav");
	m_pSourceVoice[SE_iSoundIndex["B_SPECIAL"]]->SetVolume(0.5f, 0);

	//ダメージ
	SE_iSoundIndex["B_DAMAGE"] = LoadSound("Sound/SE/bomb_sound/bomb_damage.wav");
	m_pSourceVoice[SE_iSoundIndex["B_DAMAGE"]]->SetVolume(3.0f, 0);

	//ダメージヒット
	SE_iSoundIndex["B_DAMAGE_HIT"] = LoadSound("Sound/SE/bomb_sound/bomb_hit.wav");
	m_pSourceVoice[SE_iSoundIndex["B_DAMAGE_HIT"]]->SetVolume(3.0f, 0);

	//死亡
	SE_iSoundIndex["B_DEAD"] = LoadSound("Sound/SE/bomb_sound/bomb_deth.wav");
	m_pSourceVoice[SE_iSoundIndex["B_DEAD"]]->SetVolume(3.0f, 0);

	//チャージ
	SE_iSoundIndex["B_CHARGE"] = LoadSound("Sound/SE/bomb_sound/b_Charge.wav");
	m_pSourceVoice[SE_iSoundIndex["B_CHARGE"]]->SetVolume(3.0f, 0);

	//============姫============//
	//死亡
	SE_iSoundIndex["P_DEAD"] = LoadSound("Sound/SE/princess_sound/princessdamage.wav");

	//クリア失敗
	SE_iSoundIndex["P_FAILED"] = LoadSound("Sound/SE/princess_sound/princesslose.wav");

	//クリア成功
	SE_iSoundIndex["P_CLEAR"] = LoadSound("Sound/SE/princess_sound/princesswin.wav");

	//蘇生
	SE_iSoundIndex["P_RES"] = LoadSound("Sound/SE/princess_sound/q_Resuscitation.wav");
	
	//封印
	SE_iSoundIndex["P_SEAL"] = LoadSound("Sound/SE/princess_sound/q_Sealed.wav");

	//ステージクリア
	SE_iSoundIndex["P_STEGECLEAR"] = LoadSound("Sound/SE/princess_sound/game_Clear.wav");
}

//
//	@brief				音の読み込み
//	@param(szFileName)	パス
int Sound::LoadSound(char* szFileName)
{
	static int iIndex = -1;
	iIndex++;
	HMMIO			hMmio = NULL;	//WindowsマルチメディアAPIのハンドル(WindowsマルチメディアAPIはWAVファイル関係の操作用のAPI)
	DWORD			dwWavSize = 0;	//WAVファイル内　WAVデータのサイズ（WAVファイルはWAVデータで占められているので、ほぼファイルサイズと同一）
	WAVEFORMATEX*	pwfex;				//WAVのフォーマット 例）16ビット、44100Hz、ステレオなど
	MMCKINFO		ckInfo;				//　チャンク情報
	MMCKINFO		riffckInfo;			// 最上部チャンク（RIFFチャンク）保存用
	PCMWAVEFORMAT	pcmWaveForm;

	hMmio = mmioOpenA(szFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);	//WAVファイル内のヘッダー情報（音データ以外）の確認と読み込み
	mmioDescend(hMmio, &riffckInfo, NULL, 0);						//ファイルポインタをRIFFチャンクの先頭にセットする
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');					// ファイルポインタを'f' 'm' 't' ' ' チャンクにセットする
	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);

	//フォーマットを読み込む
	mmioRead(hMmio, (HPSTR)&pcmWaveForm, sizeof(pcmWaveForm));
	pwfex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	memcpy(pwfex, &pcmWaveForm, sizeof(pcmWaveForm));
	pwfex->cbSize = 0;
	mmioAscend(hMmio, &ckInfo, 0);

	// WAVファイル内の音データの読み込み	
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);		//データチャンクにセット
	dwWavSize = ckInfo.cksize;
	m_pWavBuffer[iIndex] = new BYTE[dwWavSize];
	DWORD dwOffset = ckInfo.dwDataOffset;
	mmioRead(hMmio, (HPSTR)m_pWavBuffer[iIndex], dwWavSize);

	//ソースボイスにデータを詰め込む	
	if (FAILED(m_pXAudio2->CreateSourceVoice(&m_pSourceVoice[iIndex], pwfex)))
	{
		MessageBox(0, L"ソースボイス作成失敗", 0, MB_OK);
		return E_FAIL;
	}
	m_dwWavSize[iIndex] = dwWavSize;
	return iIndex;
}

//
//	@brief				再生
//	@param(iSoundIndex)	再生する番号
//	@param(loopflg)		ループフラグ
void  Sound::PlaySound(int iSoundIndex, bool loopflg)
{
	m_pSourceVoice[iSoundIndex]->Stop(0, 1);
	m_pSourceVoice[iSoundIndex]->FlushSourceBuffers();
	XAUDIO2_BUFFER buffer = { 0 };
	buffer.pAudioData = m_pWavBuffer[iSoundIndex];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = m_dwWavSize[iSoundIndex];
	if (loopflg)
	{
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	if (FAILED(m_pSourceVoice[iSoundIndex]->SubmitSourceBuffer(&buffer)))
	{
		MessageBox(0, L"ソースボイスにサブミット失敗", 0, MB_OK);
		return;
	}
	m_pSourceVoice[iSoundIndex]->Start(0, XAUDIO2_COMMIT_NOW);
}

//
//	@brief	初期化
HRESULT Sound::InitSound()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if (FAILED(XAudio2Create(&m_pXAudio2,0 )))
	{
		CoUninitialize();
		return E_FAIL;
	}
	if (FAILED(m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice)))
	{
		CoUninitialize();
		return E_FAIL;
	}
	return S_OK;
}
