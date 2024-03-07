cbuffer ConstantBuffer0 : register(b0)
{
    row_major matrix wvp;
};

cbuffer ConstantBuffer1 : register(b1)
{
    row_major matrix wvp_light;
};

struct VSInput
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float4 pos_light : POSITION_LIGHT;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput)0;
    {
        output.pos = mul(float4(input.pos, 1), wvp);
        output.normal = input.normal;
        output.pos_light = mul(float4(input.pos, 1), wvp_light);
    }
    return output;
}
