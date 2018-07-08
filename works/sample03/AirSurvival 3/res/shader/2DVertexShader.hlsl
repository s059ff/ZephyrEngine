cbuffer ConstantBuffer : register(b0)
{
    row_major matrix g_wvp;
};

void pass0(
    in  float4 pos : POSITION,
    out float4 o_pos : SV_POSITION)
{
    o_pos = mul(pos, g_wvp);
}

void pass1(
    in  float4 pos : POSITION,
    in  float2 tex : TEXCOORD,
    out float4 o_pos : SV_POSITION,
    out float2 o_tex : TEXCOORD)
{
    o_pos = mul(pos, g_wvp);
    o_tex = tex;
}

void pass2(
    in  float4 pos : POSITION,
    in  float2 tex : TEXCOORD,
    out float4 o_pos : SV_POSITION,
    out float2 o_tex : TEXCOORD)
{
    pass1(pos, tex, o_pos, o_tex);
}
