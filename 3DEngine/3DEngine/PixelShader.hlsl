struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    unsigned int time;
}

float4 psmain(PS_INPUT input_obj) : SV_TARGET
{
    return float4(lerp(input_obj.color, input_obj.color1, (sin(time / 500.0f) + 1.0f) / 2.0f),
    1.0f);
}