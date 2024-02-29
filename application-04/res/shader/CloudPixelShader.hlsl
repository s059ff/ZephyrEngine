SamplerState g_sampler : register(s0);

Texture2D g_texture : register(t0);

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
    float distance : DISTANCE;
};

float4 main(PSInput input) : SV_TARGET
{
    float d = min(input.distance / 4096.0f, 1.0f);
    return float4(1, 1, 1, (1 - d) * 0.05f) * g_texture.Sample(g_sampler, input.tex);
}
