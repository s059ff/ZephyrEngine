#define INSTANCE_COUNT 64

cbuffer C0 : register(b0)
{
    row_major matrix wvps[INSTANCE_COUNT];
}

cbuffer C1 : register(b1)
{
    // Only the X element is used, and the Y, Z, W elements are dummy.
    float4 alphas[INSTANCE_COUNT];
}

cbuffer C2 : register(b2)
{
    // Only the X element is used, and the Y, Z, W elements are dummy.
    float4 texindices[INSTANCE_COUNT];
}

struct VSInput
{
    float3 pos : POSITION;
    float2 texcoord : TEXCOORD;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float2 texcoord : TEXCOORD;
    float alpha : ALPHA;
    float texindex : TEXINDEX;
};

VSOutput main(VSInput input, uint instanceID : SV_INSTANCEID)
{
    VSOutput output = (VSOutput)0;
    {
        output.pos = mul(float4(input.pos, 1), wvps[instanceID]);
        output.texcoord = input.texcoord;
        output.alpha = alphas[instanceID].x;
        output.texindex = texindices[instanceID].x;
    }
    return output;
}
