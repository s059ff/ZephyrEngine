cbuffer ConstantBuffer : register(b0)
{
    row_major matrix world;
    row_major matrix viewing;
    row_major matrix projection;
};

struct VSInput
{
    float4 pos : POSITION;
    float2 tex : TEXCOORD;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput)0;
    {
        output.pos = mul(mul(mul(input.pos, world), viewing), projection);
        output.tex = input.tex;
    }
    return output;
}
