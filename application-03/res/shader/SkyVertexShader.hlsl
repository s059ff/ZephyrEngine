
cbuffer ConstantBuffer : register(b0)
{
    row_major matrix wvp;
};

struct VSInput
{
    float3 pos : POSITION;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float3 tex : TEXCOORD;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput)0;
    {
        output.pos = mul(float4(input.pos, 1), wvp);
        output.tex = input.pos;
    }
    return output;
}
