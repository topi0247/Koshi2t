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
	
	HRESULT Init(ID3D11DeviceContext* pContext,DWORD width,DWORD height,float size,D3DXVECTOR4 vColor);
	void Render(char* text,int x,int y);
	void RenderFont(int FontIndex,int x,int y);

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	ID3D11SamplerState* m_pSampleLinear;	
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11Buffer* m_pConstantBuffer;
	ID3D11BlendState* m_pBlendState;


	DWORD m_dwWindowWidth;
	DWORD m_dwWindowHeight;
	ID3D11ShaderResourceView* m_pAsciiTexture;
	ID3D11Buffer* m_pVertexBuffer[100];
	D3DXMATRIX m_mView;
	D3DXMATRIX m_mProj;
	float m_fKerning[100];
	float m_fScale;//25pixelを基準 25pixel=1.0f
	float m_fAlpha;
	D3DXVECTOR4 m_vColor;
};