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

struct PSInput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD;
};

float4 main(PSInput input) : SV_TARGET
{
    float3 ld = -light_direction.xyz;
    float3 n = normalize(mul(float4(input.normal, 0), w).xyz);
    float k = clamp(dot(ld, n), 0.0f, 1.0f);

    float3 color = k * g_texture.Sample(g_sampler, input.tex).rgb;

    return float4(color, 1);
}
