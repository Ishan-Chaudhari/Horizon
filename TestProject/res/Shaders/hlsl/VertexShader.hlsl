
struct VS_OUTPUT
{
	float3 color : COLOR;
	float2 texc : TEXC;
	float4 position : SV_POSITION;
};

cbuffer Wvp : register(b0)
{
	float4x4 Transform;
	float4x4 World;
};

VS_OUTPUT main(float3 pos : POSITION, float3 col : NORMAL,float2 tex : TEXC)
{
	VS_OUTPUT vo;
	
	vo.color = col;
	vo.texc = tex;
	vo.position = mul(float4(pos, 1.f), Transform);
	
	return vo;
}