#include "FBX.hlsli"

//0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex : register(t0);
//0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[
SamplerState smp : register(s0);

struct PSOutput
{
	float4 target0 : SV_TARGET0;
	float4 target1 : SV_TARGET1;
};
//�G���g���[�|�C���g
PSOutput main(VSOutput input)
{
	PSOutput output;
	//�e�N�X�`���\�}�b�s���O
	float4 texcolor = tex.Sample(smp, input.uv);
	//Lambert����
	float3 light = normalize(float3(1, -1, 1)); //�E�����@�������C�g
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

	//�A�e�ƃe�N�X�`���̐F������
	output.target0 = shadecolor * texcolor;
	output.target1 = shadecolor * texcolor;
	return output;
}