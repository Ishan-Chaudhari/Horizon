
cbuffer Material : register(b0)
{
	float3 M_color;
	float3 M_specular;
	float  M_metallic;
	float  M_roughness;
};

cbuffer Light : register(b1)
{
	float3 L_position;
	float3 L_color;
	float2 Null;
};

cbuffer Camera : register(b2)
{
	float3 C_Position;
	float null;
};

float4 main(float3 norm : NORMAL, float2 TexCoord : TEXC, float3 FragPos : FRAGPOS) : SV_TARGET
{
	float3 ambient = M_color * L_color * 0.3f;

	float3 Normal = normalize(norm);
	float3 LightDir = normalize(L_position - FragPos);
	float diff = max(dot(LightDir, Normal), 0.f);
	float3 diffuse = M_color * L_color * diff;

	float3 ViewDir = normalize(C_Position - FragPos);
	float3 ReflDir = reflect(LightDir, Normal);
	float spec = pow(max(dot(ViewDir, ReflDir), 0.f), 64.f);
	float3 specular = M_color * L_color * spec;

	return float4(ambient + diffuse + specular, 1.0f);
}