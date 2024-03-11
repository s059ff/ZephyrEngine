cbuffer C0 : register(b0)
{
    row_major matrix world;
    row_major matrix viewing;
    row_major matrix projection;
}

cbuffer C1 : register(b1)
{
    float texindex;
    float _dummy1, _dummy2, _dummy3;  // All constant buffers must be 16-byte aligned.
}

struct VSInput
{
    float4 pos : POSITION;
    float2 tex : TEXCOORD;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
    float texindex : TEXINDEX;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput)0;
    {
        output.pos = mul(mul(mul(input.pos, world), viewing), projection);
        output.tex = input.tex;
        output.texindex = texindex;
    }
    return output;
}
