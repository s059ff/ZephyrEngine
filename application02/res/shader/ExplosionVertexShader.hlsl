#define INSTANCE_COUNT 64

struct VSInput
{
    float3 pos : POSITION;
    float2 tex : TEXCOORD;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
    float4 color : COLOR;
};

cbuffer C0 : register(b0)
{
    row_major matrix wvps[INSTANCE_COUNT];
};

cbuffer C1 : register(b1)
{
    float4 colors[INSTANCE_COUNT];
};

VSOutput main(VSInput input, uint instanceID : SV_INSTANCEID)
{
    VSOutput output = (VSOutput)0;
    {
        output.pos = mul(float4(input.pos, 1), wvps[instanceID]);
        output.tex = input.tex;
        output.color = colors[instanceID];
    }
    return output;
}
