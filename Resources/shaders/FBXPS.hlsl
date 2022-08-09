#include "FBX.hlsli"

//0番スロットに設定されたテクスチャ
Texture2D<float4> tex : register(t0);
//0番スロットに設定されたサンプラー
SamplerState smp : register(s0);

struct PSOutput
{
	float4 target0 : SV_TARGET0;
	float4 target1 : SV_TARGET1;
};
//エントリーポイント
PSOutput main(VSOutput input)
{
	PSOutput output;
	//テクスチャ―マッピング
	float4 texcolor = tex.Sample(smp, input.uv);
	//Lambert反射
	float3 light = normalize(float3(1, -1, 1)); //右下奥　向きライト
	float diffuse = saturate(dot(-light, input.normal));
	float brightness = diffuse + 0.3f;
	float4 shadecolor = float4(brightness, brightness, brightness, 1.0f);
	const float shininess = 4.0f;
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
	float3 dotlightnormal = dot(lightv, input.normal);
	float3 reflect = normalize(-lightv + 2 * dotlightnormal * input.normal);
	float3 ambient = m_ambient;
	float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;


	/*shadecolor.rgb = (ambient + diffuse + specular) * lightcolor;
	shadecolor.a = m_alpha;*/

	//陰影とテクスチャの色を合成
	output.target0 = shadecolor * texcolor;
	output.target1 = shadecolor * texcolor;
	return output;
}