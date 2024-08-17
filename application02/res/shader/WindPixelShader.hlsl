SamplerState g_sampler : register(s0);

Texture2D g_texture : register(t0);

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
    float alpha : ALPHA;
};

static const float M_PI = 3.141592653589793;

float4 main(PSInput input) : SV_TARGET
{
    float alpha = cos(M_PI * (input.tex.y - 0.5f));
    return g_texture.Sample(g_sampler, input.tex) * input.alpha * alpha;
}
