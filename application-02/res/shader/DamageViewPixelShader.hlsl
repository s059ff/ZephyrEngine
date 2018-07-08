
cbuffer C0 : register(b0)
{
    float4 color;
}

float4 main(float4 pos : SV_POSITION, float2 uv : UV) : SV_TARGET
{
    float a = clamp(2.0f * length(uv) - 0.8f, 0.0f, 1.0f);
    return color * float4(1, 1, 1, a);
}
