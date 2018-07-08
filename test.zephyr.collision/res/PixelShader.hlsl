cbuffer ConstantBuffer0 : register(b0)
{
    row_major matrix w;
};
cbuffer ConstantBuffer1 : register(b1)
{
    float4 color;
};
cbuffer ConstantBuffer2 : register(b2)
{
    float4 lighting;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
};

float4 main(PSInput input) : SV_TARGET
{
    float a = clamp(dot((mul(float4(input.normal, 0), w)).xyz, normalize(float3(1, -1, 1))), 0, 1);
    return color * (0.5f * a + 0.5f);
}
