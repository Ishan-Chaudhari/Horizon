
struct VS_OUTPUT
{
	float3 color : COLOR;
	float2 texc : TEX;
	float4 position : SV_POSITION;
};

cbuffer Wvp
{
	float4x4 Transform;
};

VS_OUTPUT main(float3 pos : POSITION, float3 col : COLOR,float2 tex : TEX)
{
	VS_OUTPUT vo;
	
	vo.color = col;
	vo.texc = tex;
	vo.position = mul(float4(pos, 1.f), Transform);
	
	return vo;
}