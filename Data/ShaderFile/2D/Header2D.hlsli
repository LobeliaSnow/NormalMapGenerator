struct VS_IN_TEX
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
    float2 tex : TEXCOORD0;
};
struct VS_IN_INSTANCING_TEX
{
    float4 pos : POSITION0;
    float2 tex : TEXCOORD0;
    column_major float4x4 ndcTrans : NDC_I;
    float4 col : COLOR0_I;
    float4 uvTrans : UV_I;
    uint InstanceId : SV_InstanceID; // �C���X�^���X�h�c};
};
struct PS_IN_TEX
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
    float2 tex : TEXCOORD0;
};

