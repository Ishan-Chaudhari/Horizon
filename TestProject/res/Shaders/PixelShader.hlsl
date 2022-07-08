
texture2D tex;
SamplerState samp;

float4 main(float3 color : COLOR, float2 texCoord : TEX) : SV_TARGET
{
	return float4(color, 1.0f) * tex.Sample(samp,texCoord);
}