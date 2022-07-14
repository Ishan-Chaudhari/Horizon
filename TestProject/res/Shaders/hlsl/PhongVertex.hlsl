
struct VS_OUTPUT
{
	float3 Normal : NORMAL;
	float2 TexCoord : TEXC;
	float3 FragPos : FRAGPOS;
	float4 Position : SV_POSITION;
};

cbuffer Wvp : register(b0)
{
	float4x4 Transform;
	float4x4 World;
};

VS_OUTPUT main(float3 pos : POSITION,float3 norm : NORMAL,float2 tex : TEXC)
{
	VS_OUTPUT vo; 
	
	vo.Normal = norm;
	vo.TexCoord = tex;
	
	float4 Pos = mul(float4(pos, 1.f), World);

	vo.FragPos.x = Pos.x;
	vo.FragPos.y = Pos.y;
	vo.FragPos.z = Pos.z;
	
	vo.Position = mul(float4(pos, 1.f), Transform);

	return vo;
}