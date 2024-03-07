
struct VSInput
{
    float3 pos : POSITION;
    float2 tex : TEXCOORD;
    float alpha : ALPHA;
    float4 wvp0 : WVP0;
    float4 wvp1 : WVP1;
    float4 wvp2 : WVP2;
    float4 wvp3 : WVP3;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
    float alpha : ALPHA;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput)0;
    {
        row_major matrix wvp;
        wvp[0] = input.wvp0;
        wvp[1] = input.wvp1;
        wvp[2] = input.wvp2;
        wvp[3] = input.wvp3;
        output.pos = mul(float4(input.pos, 1), wvp);
        output.tex = input.tex;
        output.alpha = input.alpha;
    }
    return output;
}
