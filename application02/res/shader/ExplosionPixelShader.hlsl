SamplerState g_sampler : register(s0);

Texture2DArray g_texture : register(t0);

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 texcoord : TEXCOORD;
    float alpha : ALPHA;
    float texindex : TEXINDEX;
};

float4 main(PSInput input) : SV_TARGET
{
    float3 texcoord = float3(input.texcoord.x, input.texcoord.y, input.texindex);
    float4 color = g_texture.Sample(g_sampler, texcoord);
    float4 coeff = float4(input.alpha, input.alpha, input.alpha, 1.0f);
    return coeff * color;
}
