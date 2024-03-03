struct PSInput
{
    float4 pos : SV_POSITION;
    float color : COLOR;
};

float4 main(PSInput input) : SV_TARGET
{
    return input.color;
}
