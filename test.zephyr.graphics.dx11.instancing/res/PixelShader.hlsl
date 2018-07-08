static const float FLOT32_MAX = 3.402823466e+38f;

// サンプラー
SamplerState g_sampler : register(s0)
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
    AddressW = WRAP;
    MipmapLODBias = 0;
    MaxAnisotropy = 1;
    ComparisonFunc = NEVER;
    MinLOD = 0;
    MaxLOD = FLOAT32_MAX;
};

// テクスチャ
Texture2DArray g_texture : register(t0);

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
    float1 texindex : TEXINDEX;
};

float4 main(PSInput input) : SV_TARGET
{
    return g_texture.Sample(g_sampler, float3(input.tex.xy, input.texindex));
}