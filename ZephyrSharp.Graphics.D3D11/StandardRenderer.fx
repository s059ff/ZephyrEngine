float4x4 g_matrix;

float4 g_color;

texture g_texture;

sampler g_sampler = sampler_state
{
    Texture = < g_texture >;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

void vs_0(float4 pos : POSITION, out float4 o_pos : POSITION)
{
    o_pos = mul(pos, g_matrix);
}

void vs_1(float4 pos : POSITION, float2 tex : TEXCOORD, out float4 o_pos : POSITION, out float2 o_tex : TEXCOORD)
{
    o_pos = mul(pos, g_matrix);
    o_tex = tex;
}

void vs_2(float4 pos : POSITION, float4 col : COLOR, out float4 o_pos : POSITION, out float4 o_col : COLOR)
{
    o_pos = mul(pos, g_matrix);
    o_col = col;
}

void vs_3(float4 pos : POSITION, float4 col : COLOR, float2 tex : TEXCOORD, out float4 o_pos : POSITION, out float4 o_col : COLOR, out float2 o_tex : TEXCOORD)
{
    o_pos = mul(pos, g_matrix);
    o_col = col;
    o_tex = tex;
}

void ps_0(out float4 o_col : COLOR)
{
    o_col = g_color;
}

void ps_1(float2 tex : TEXCOORD, out float4 o_col : COLOR)
{
    o_col = g_color * tex2D(g_sampler, tex);
}

void ps_2(float4 col : COLOR, out float4 o_col : COLOR)
{
    o_col = g_color * col;
}

void ps_3(float4 col : COLOR, float2 tex : TEXCOORD, out float4 o_col : COLOR)
{
    o_col = g_color * col * tex2D(g_sampler, tex);
}

technique g_technique
{
    // テクスチャ/頂点カラーなし
    pass P0
    {
        VertexShader = compile vs_2_0 vs_0();
        PixelShader = compile ps_2_0 ps_0();
    }

    // テクスチャあり
    pass P1
    {
        VertexShader = compile vs_2_0 vs_1();
        PixelShader = compile ps_2_0 ps_1();
    }

    // 頂点カラーあり
    pass P2
    {
        VertexShader = compile vs_2_0 vs_2();
        PixelShader = compile ps_2_0 ps_2();
    }

    // テクスチャ/頂点カラーあり
    pass P3
    {
        VertexShader = compile vs_2_0 vs_3();
        PixelShader = compile ps_2_0 ps_3();
    }
}
