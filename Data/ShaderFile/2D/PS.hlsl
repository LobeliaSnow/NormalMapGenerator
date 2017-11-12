#include "../Header.hlsli"
#include "Header2D.hlsli"

float4 NegativeReversal(float4 color)
{
    return float4(1.0f - color.rgb, color.a);
}
float4 Grayscale(float4 color)
{
    static const float4 mono = float4(0.298912, 0.586611, 0.114478, 0.0);
    color.rgb = dot(color.rgb, mono.rgb);
    return color;
}
float4 Sepia(float4 color)
{
    static const float4 sepiaTone = float4(0.941176f, 0.784313f, 0.293103f, 1.0f);
    return Grayscale(color) * sepiaTone;
}

interface PSInterface
{
    float4 GetColor(PS_IN_TEX ps_in);
};

//�������V�F�[�_�[�����P�[�W��interface����Ες���������
class TextureColor : PSInterface
{
    float4 GetColor(PS_IN_TEX ps_in)
    {
        return txDiffuse.Sample(samLinear, ps_in.tex);
    }
};

class VertexColor : PSInterface
{
    float4 GetColor(PS_IN_TEX ps_in)
    {
        return float4(0, 0, 0, 1);
    }
};
class InvertTextureColor : PSInterface
{
    float4 GetColor(PS_IN_TEX ps_in)
    {
        return NegativeReversal(txDiffuse.Sample(samLinear, ps_in.tex));
    }
};
class GrayscaleTextureColor : PSInterface
{
    float4 GetColor(PS_IN_TEX ps_in)
    {
        return Grayscale(txDiffuse.Sample(samLinear, ps_in.tex));
    }
};
class SepiaTextureColor : PSInterface
{
    float4 GetColor(PS_IN_TEX ps_in)
    {
        return Sepia(txDiffuse.Sample(samLinear, ps_in.tex));
    }
};

//�܂�܂Ƃ͂܂����̂Ń���
//�V�F�[�_�[�����P�[�W����ۂɁAinterface�ɑ΂���class����̏ꍇ
//����ȊO�ɌĂяo�����\����0�Ȃ̂ōœK���ŃC�����C���W�J����Ă��܂�
//���̃C���^�[�t�F�[�X�̃C���X�^���X��������B
PSInterface ps;

float4 Main2D(PS_IN_TEX ps_in) : SV_Target
{
    return ps.GetColor(ps_in) * ps_in.col;
}