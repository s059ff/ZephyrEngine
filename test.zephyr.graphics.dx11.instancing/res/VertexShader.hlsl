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
    float2 offset : OFFSET;
    float1 texindex : TEXINDEX;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
    float1 texindex : TEXINDEX;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput)0;
    {
        input.pos.xy += input.offset.xy;
        output.pos = mul(mul(mul(input.pos, world), viewing), projection);
        output.tex = input.tex;
        output.texindex = input.texindex;
    }
    return output;
}
