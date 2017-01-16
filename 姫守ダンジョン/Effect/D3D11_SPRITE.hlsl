//グローバル

Texture2D g_texColor: register(t0);//テクスチャーは レジスターt(n)
SamplerState g_samLinear : register(s0);//サンプラーはレジスターs(n)

cbuffer global
{
	matrix g_mWVP; //ワールドから射影までの変換行列
	float4 g_vDiffuse;//ディフューズ色
	float g_fAlpha;
	float4 g_TexScroll;
};

//構造体
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
};

//
//バーテックスシェーダー
//
VS_OUTPUT VS( float4 Pos : POSITION ,float2 Tex : TEXCOORD )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul(Pos,g_mWVP);
    output.Tex = Tex;
	output.Tex.x += g_TexScroll.x;
//	output.Tex.y = g_TexScroll.y;
    return output;
}

//
//ピクセルシェーダー
//
float4 PS( VS_OUTPUT input  ) : SV_Target
{
	return (g_vDiffuse*g_texColor.Sample( g_samLinear, input.Tex ))*g_fAlpha;
}