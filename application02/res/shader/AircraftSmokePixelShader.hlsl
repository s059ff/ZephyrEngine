SamplerState g_sampler : register(s0);

Texture2D g_texture : register(t0);

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
    float alpha : ALPHA;
};

float4 main(PSInput input) : SV_TARGET
{
    float alpha = input.alpha * g_texture.Sample(g_sampler, input.tex).r;
    float4 color = float4(alpha, alpha, alpha, alpha);
    return color;
}
