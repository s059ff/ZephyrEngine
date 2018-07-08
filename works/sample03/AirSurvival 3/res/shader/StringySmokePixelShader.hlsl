SamplerState g_sampler : register(s0);

Texture2D g_texture : register(t0);

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
    float4 color : COLOR;
};

float4 main(PSInput input) : SV_TARGET
{
    return g_texture.Sample(g_sampler, input.tex) * input.color;
}
