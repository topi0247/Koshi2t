#pragma once

#include <windows.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")


#define SAFE_RELEASE(x) if(x){x->Release(); x=NULL;}
#define DIMENSION 24.0f
#define WDIMENSION 20.0f
#define TEX_DIMENSION 256.0f

//
//
struct TEXT_CONSTANT_BUFFER
{
	D3DXMATRIX mWVP;
	D3DXVECTOR4 vColor;
	D3DXVECTOR4 fAlpha;
};
//
//
struct TextVertex
{
	D3DXVECTOR3 Pos; //位置
	D3DXVECTOR2 vTex; //テクスチャー座標
};
//
//
class D3D11_TEXT
{
public:
	D3D11_TEXT();
	~D3D11_TEXT();
	
	static HRESULT Init(ID3D11DeviceContext* pContext,DWORD width,DWORD height,float size,D3DXVECTOR4 vColor);
	static void SetCamera(D3DXMATRIX view, D3DXMATRIX proj);
	void Render(char* text,int x,int y);
	void RenderFont(int FontIndex,int x,int y);

	static ID3D11Device* m_pDevice;
	static ID3D11DeviceContext* m_pDeviceContext;
	static ID3D11SamplerState* m_pSampleLinear;
	static ID3D11VertexShader* m_pVertexShader;
	static ID3D11PixelShader* m_pPixelShader;
	static ID3D11InputLayout* m_pVertexLayout;
	static ID3D11Buffer* m_pConstantBuffer;
	static ID3D11BlendState* m_pBlendState;


	static DWORD m_dwWindowWidth;
	static DWORD m_dwWindowHeight;
	static ID3D11ShaderResourceView* m_pAsciiTexture;
	static ID3D11Buffer* m_pVertexBuffer[100];
	static D3DXMATRIX m_mView;
	static D3DXMATRIX m_mProj;
	static float m_fKerning[100];
	static float m_fScale;//25pixelを基準 25pixel=1.0f
	static float m_fAlpha;
	static D3DXVECTOR4 m_vColor;
};