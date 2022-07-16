#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);  // 1番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	/*float2 xy = { 0.5f,0.0f };*/
  /*  float pixX = 1 / 1280;
	float pixY = 1 / 720;
	float4 firstColor = { 0,0,0,0 };
	for (float i = 0; i < 1; i += pixY)
	{
		for (float i = 0; i < 1; i += pixX)
		{

		}
	}*/
	/*float4 texcolor = tex.Sample(smp, input.uv);
	return float4(texcolor.rgb, 1);*/
	//return float4(1.0f - texcolor.rgb, 1);
	float4 colortex0 = tex0.Sample(smp, input.uv);
	float4 colortex1 = tex1.Sample(smp, input.uv);

	float4 color = colortex0;
	if (fmod(input.uv.y, 0.1f) < 0.05f) {
		color = colortex1;
	}

	return float4(color.rgb, 1);
}