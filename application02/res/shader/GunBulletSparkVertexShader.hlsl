cbuffer ConstantBuffer : register(b0)
{
    row_major matrix wvp;
};

void main(
    in float3 pos : POSITION,
    in float4 color : COLOR,
    in float4 wvp0 : WVP0,
    in float4 wvp1 : WVP1,
    in float4 wvp2 : WVP2,
    in float4 wvp3 : WVP3,
    in float1 alpha : ALPHA,
    out float4 o_pos : SV_POSITION,
    out float4 o_color : COLOR)
{
    row_major matrix wvp;
    wvp[0] = wvp0;
    wvp[1] = wvp1;
    wvp[2] = wvp2;
    wvp[3] = wvp3;

    o_pos = mul(float4(pos, 1), wvp);
    o_color = alpha * color;
}
