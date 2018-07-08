struct GSInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

struct GSOutput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

[maxvertexcount(3)]
void main(
    triangle GSInput input[3],
    inout TriangleStream< GSOutput > output
)
{
    GSOutput element;

    for (uint i = 0; i < 3; i++)
    {
        element.pos = input[i].pos;
        element.tex = input[i].tex;
        output.Append(element);
    }

    output.RestartStrip();
}
