
Texture2D tex;
SamplerState samp;

float4 main(float3 color : COLOR, float2 texCoord : TEXC) : SV_TARGET
{
	//return tex.Sample(samp,texCoord);
	return float4(color, 1.0f) ;
}