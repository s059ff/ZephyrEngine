SamplerState g_sampler : register(s0);

Texture2D g_texture : register(t0);

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

float4 main(PSInput input) : SV_TARGET
{
    return float4(0.2f, 0.1f, 0.4f, 1.0f) * g_texture.Sample(g_sampler, input.tex).r;
}
