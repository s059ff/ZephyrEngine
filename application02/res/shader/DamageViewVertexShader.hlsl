
void main(
    float4 pos : POSITION,
    out float4 o_pos : SV_POSITION,
    out float2 o_uv : UV)
{
    pos.xy *= 2;
    o_pos = pos;
    o_uv = pos.xy;
}
