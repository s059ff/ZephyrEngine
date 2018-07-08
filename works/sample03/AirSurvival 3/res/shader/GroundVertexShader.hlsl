cbuffer ConstantBuffer : register(b0)
{
    row_major matrix wvp;
};

struct VSInput
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD0;
    float2 tex2 : TEXCOORD1;
    float distance : DISTANCE;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput)0;
    {
        output.pos = mul(float4(input.pos, 1), wvp);
        output.normal = input.normal;
        output.tex = input.tex;
        output.tex2 = float2(0.5f + input.pos.x, 0.5f + input.pos.z);
        output.distance = output.pos.w;
    }
    return output;
}
