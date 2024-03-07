cbuffer ConstantBuffer : register(b0)
{
    float4 g_color;
};

cbuffer ConstantBuffer : register(b1)
{
    float4 color_threshold_lower;
    float4 color_threshold_upper;
};

cbuffer ConstantBuffer : register(b2)
{
    float2 tex_threshold_lower;
    float2 tex_threshold_upper;
};

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
    MaxLOD = 3.402823466e+38f;
};

Texture2D g_texture : register(t0);

// テクスチャなし
float4 pass0(float4 pos : SV_POSITION) : SV_TARGET
{
    float4 color = g_color;
    if (color.a == 0)
        discard;
    return color;
}

// テクスチャあり
float4 pass1(
    float4 pos : SV_POSITION,
    float2 tex : TEXCOORD) : SV_TARGET
{
    float4 color = g_color * g_texture.Sample(g_sampler, tex);
    if (color.a == 0)
        discard;
    return color;
}

// 閾値あり
float4 pass2(
    float4 pos : SV_POSITION,
    float2 tex : TEXCOORD) : SV_TARGET
{
    float4 color = g_color * g_texture.Sample(g_sampler, tex);
    if (color.a == 0 ||
        color.r < color_threshold_lower.r || color_threshold_upper.r < color.r ||
        color.g < color_threshold_lower.g || color_threshold_upper.g < color.g ||
        color.b < color_threshold_lower.b || color_threshold_upper.b < color.b ||
        color.a < color_threshold_lower.a || color_threshold_upper.a < color.a ||
        tex.x < tex_threshold_lower.x || tex_threshold_upper.x < tex.x ||
        tex.y < tex_threshold_lower.y || tex_threshold_upper.y < tex.y)
        discard;
    return color;
}
