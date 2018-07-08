cbuffer ConstantBuffer0 : register(b0)
{
    row_major matrix w;
};

cbuffer ConstantBuffer1 : register(b1)
{
    float4 light_direction;
};

SamplerState g_sampler : register(s0);

Texture2D g_texture : register(t0);
Texture2D g_texture2 : register(t1);
Texture2D g_mixing_rate_texture : register(t2);

struct PSInput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD0;
    float2 tex2 : TEXCOORD1;
    float distance : DISTANCE;
};

float4 main(PSInput input) : SV_TARGET
{
    float3 ld = -light_direction.xyz;
    float3 n = normalize(mul(float4(input.normal, 0), w).xyz);
    float k = clamp(dot(ld, n), 0.0f, 1.0f);

    float3 color1 = g_texture.Sample(g_sampler, input.tex).rgb;
    float3 color2 = g_texture2.Sample(g_sampler, input.tex).rgb;

    float rate = g_mixing_rate_texture.Sample(g_sampler, input.tex2).r;
    float3 color = rate * color1 + (1 - rate) * color2;

    float d = min(input.distance / 3072.0f, 1.0f);
    color = k * (1 - d) * color + d * (float3(0.5f, 0.7f, 0.8f) - 0.2f);

    return float4(color, 1);
}
