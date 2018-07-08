cbuffer C0 : register(b0)
{
    row_major matrix wvp;
};

struct VSInput
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float distance : DISTANCE;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput)0;
    {
        output.pos = mul(float4(input.pos, 1), wvp);
        output.normal = input.normal;
        output.tex = input.tex;
        output.tangent = input.tangent;
        output.binormal = input.binormal;
        output.distance = output.pos.w;
    }
    return output;
}
