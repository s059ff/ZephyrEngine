cbuffer ConstantBuffer : register(b0)
{
    row_major matrix wvp;
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
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput)0;
    {
        output.pos = mul(float4(input.pos, 1), wvp);
        output.normal = input.normal;
    }
    return output;
}
