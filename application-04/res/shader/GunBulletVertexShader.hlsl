cbuffer ConstantBuffer : register(b0)
{
    row_major matrix vp;
};

cbuffer ConstantBuffer : register(b1)
{
    float4 points[2];
};

void main(
    int index : INDEX,
    out float4 o_pos : SV_POSITION,
    out float4 o_color : COLOR)
{
    float4 colors[2] = { float4(1, 1, 0, 1), float4(0, 0, 0, 0) };

    o_pos = mul(points[index], vp);
    o_color = colors[index];
}
