#pragma once
#include "../Origin.h"
//#include "../MAIN.h"


struct SIMPLESHADER_CONSTANT_BUFFER
{
	D3DXMATRIX mWVP;
	D3DXVECTOR4 vColor;
	D3DXVECTOR4 fAlpha;
};
//
//
struct SimpleVertex
{
	D3DXVECTOR3 Pos; //位置
	D3DXVECTOR2 vTex; //テクスチャー座標
};
//
//
struct GrapRect
{
	GrapRect(float top, float bottom, float left, float right){
		m_top = top;
		m_bottom = bottom;
		m_left = left;
		m_right = right;
	}
	~GrapRect(){}

	float m_top;
	float m_bottom;
	float m_left;
	float m_right;
};
//
//
class TD_Graphics
{
public:
	TD_Graphics();
	~TD_Graphics();

	static HRESULT InitDevice(ID3D11DeviceContext* pContext);


	// @param (textname)	textureパス
	// @param (texnum)		？？
	// @param (drawpos)		描画座標
	// @param (texsize)     画像サイズ
	// @param (vColor)		色
	// @param (_Rect)		レクト
	HRESULT Init(LPCWSTR texname, int texnum, D3DXVECTOR2 drawpos, D3DXVECTOR2 texsize, D3DXVECTOR4 vColor, GrapRect _Rect);
	void	Render(char* text, int dnum, int x, int y);
	void	RenderFont(int FontIndex, int x, int y);
	void	SetBlend_Desc();
	void	StopBlendState() {
		dd.RenderTarget[0].BlendEnable = false;
		m_pDevice->CreateBlendState(&dd, &m_pBlendState);
	}
	void StartBlendState() {
		dd.RenderTarget[0].BlendEnable = true;
		m_pDevice->CreateBlendState(&dd, &m_pBlendState);
	}

	ID3D11BlendState*			m_pBlendState;
	D3D11_BLEND_DESC			dd;
	HRESULT						InitTex(LPCWSTR textname, int texnum, D3DXVECTOR2 drawpos, D3DXVECTOR2 texsize, D3DXVECTOR4 vColor);
private:
	static ID3D11Device*				m_pDevice;
	static ID3D11DeviceContext*			m_pDeviceContext;
	static ID3D11SamplerState*			m_pSampleLinear;
	static ID3D11VertexShader*			m_pVertexShader;
	static ID3D11PixelShader*			m_pPixelShader;
	static 	ID3D11InputLayout*			m_pVertexLayout;
	static ID3D11Buffer*				m_pConstantBuffer;

	DWORD						m_dwWindowWidth;
	DWORD						m_dwWindowHeight;
	ID3D11ShaderResourceView*	m_pAsciiTexture[PIC2D_NUM];
	ID3D11Buffer*				m_pVertexBuffer[100];
	ID3D11Buffer*				m_RectBuffer;
	D3DXMATRIX					m_mView;
	D3DXMATRIX					m_mProj;
	float						m_fKerning[100];
	float						m_fScale;				//25pixelを基準 25pixel=1.0f
	float						m_fAlpha;
	D3DXVECTOR4					m_vColor;
	int							drawnum;
};