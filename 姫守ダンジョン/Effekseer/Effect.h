#pragma once
#include <map>
#include <string>
#include <vector>
#include <assert.h>
#include "../Origin.h"
#define MAX 100

using namespace std;

class Effect
{
private:
	Effect();
	~Effect();
	static ::Effekseer::Manager*			g_manager;
	static ::EffekseerRenderer::Renderer*	g_renderer;
	::Effekseer::Handle						g_handle[MAX];
	::Effekseer::Effect*					g_effect[MAX];

	static ID3D11Device*				g_device;
	static ID3D11DeviceContext*			g_context;
	void EffectSet();
public:

	Effect(const Effect&) = delete;
	Effect& operator = (const Effect&) = delete;
	Effect(Effect&&) = delete;
	Effect& operator=(Effect&&) = delete;

	static Effect& getInstance()
	{
		static Effect inst;
		return inst;
	}

	void EffectInit(HWND, ID3D11Device*, ID3D11DeviceContext*);
	int LoadEffect(const EFK_CHAR* path);
	void SetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look);
	void Set();
	void Effect_Play(string name, D3DXVECTOR3 pos);
	void Effect_Stop(string name);
	void SetScale(string name, float scale);
	void SetRotation(string name, D3DXVECTOR3 angle);
	void SetRotation(string name, D3DXVECTOR3 pos, float angle);
	void Update();
	void Update(string name, D3DXVECTOR3 pos);
	void Draw();
};