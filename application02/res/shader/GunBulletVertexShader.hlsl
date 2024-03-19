cbuffer ConstantBuffer : register(b0)
{
    row_major matrix wvp;
};

cbuffer ConstantBuffer : register(b1)
{
    float4 points[2];
};

void main(
    in float3 pos : POSITION,
    in float4 color : COLOR,
    out float4 o_pos : SV_POSITION,
    out float4 o_color : COLOR)
{
    o_pos = mul(float4(pos, 1), wvp);
    o_color = color;
}
