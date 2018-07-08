cbuffer ConstantBuffer : register(b0)
{
    row_major matrix wvp;
};

void main(
    float3 pos : POSITION, 
    out float4 o_pos : SV_POSITION,
    inout float2 tex : TEXCOORD)
{
    o_pos = mul(float4(pos, 1), wvp);
}
