static const float FLOT32_MAX = 3.402823466e+38f;

SamplerState g_sampler : register(s0);

TextureCube g_texture : register(t0);

struct PSInput
{
    float4 pos : SV_POSITION;
    float3 tex : TEXCOORD;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 color = g_texture.Sample(g_sampler, input.tex);
    float r = min(pow((input.tex.y - 0.5f) / 0.5f, 2), 1.0f);
    color = (1 - r) * color + r * float4(0.5f, 0.7f, 0.8f, 1.0f);
    color.rgb -= 0.2f;
    color.a = 1.0f;
    return color;
}
