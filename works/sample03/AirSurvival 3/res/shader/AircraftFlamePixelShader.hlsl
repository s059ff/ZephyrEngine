#define INSTANCE_COUNT 64

SamplerState g_sampler : register(s0);

Texture2DArray g_texture : register(t0);

cbuffer C0 : register(b0)
{
    float4 colors[INSTANCE_COUNT];
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
    uint instanceID : INSTANCEID;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 color = g_texture.Sample(g_sampler, float3(input.tex, colors[input.instanceID].a)) * colors[input.instanceID];
    color.gb *= 0.5f;
    return color;
}
