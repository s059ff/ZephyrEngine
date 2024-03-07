SamplerState g_sampler : register(s0);

Texture2D g_texture : register(t0);

cbuffer ConstantBuffer : register(b0)
{
    float4 g_color;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 color = g_texture.Sample(g_sampler, input.tex);
    return color * g_color;
}
