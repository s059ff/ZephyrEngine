cbuffer ConstantBuffer0 : register(b0)
{
    row_major matrix w;
};

cbuffer ConstantBuffer2 : register(b2)
{
    float4 light_direction;
};

SamplerState g_sampler : register(s0);

SamplerComparisonState g_comparator : register(s1);

Texture2D g_texture : register(t0);

Texture2D g_depthmap : register(t1);

struct PSInput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD;
    float4 pos_light : POSITION_LIGHT;
};

float4 main(PSInput input) : SV_TARGET
{
    float4 uvz = input.pos_light;
    uvz /= uvz.w;
    uvz.x = uvz.x * 0.5f + 0.5f;
    uvz.y = -uvz.y * 0.5f + 0.5f;
    uvz.z -= 0.01f;

    float k = g_depthmap.SampleCmpLevelZero(g_comparator, uvz.xy, uvz.z);

    float a = clamp(dot(normalize(mul(float4(input.normal, 0), w).xyz), light_direction.xyz), 0.25f, 1);
    //return g_texture.Sample(g_sampler, input.tex) * a * clamp(k, 0.5f, 1.0f);
    return float4(0.2f, 0.4f, 0.8f, 1.0f) * a * clamp(k, 0.5f, 1.0f);
}
