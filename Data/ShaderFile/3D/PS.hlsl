#include "../Header.hlsli"
#include "Header3D.hlsli"

float IndexFog(float4 pos)
{
    static const float e = 2.71828f;
	//����
    float dist = pos.z * pos.w;
	//���x
    float density = fogInfo.w;
     //�t�H�O�t�@�N�^�[
    float f = pow(e, -dist * density);
	//�t�H�O�̗�
    f *= 1.0f;
    f = saturate(f);

    return f;
}

float4 Main3D(PS_IN ps_in) : SV_Target
{
    float4 diffuseColor = txDiffuse.Sample(samLinear, ps_in.tex) * texColor * ps_in.color * ambientColor;
    float fog = IndexFog(ps_in.pos);
    return float4(fog * diffuseColor.xyz + (1.0f - fog) * fogInfo.rgb, diffuseColor.a);
}