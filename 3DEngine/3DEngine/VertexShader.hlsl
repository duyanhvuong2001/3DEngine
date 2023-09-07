struct VS_INPUT
{
    float4 position : POSITION;
    float4 position1 : POSITION1;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

//constant attr
cbuffer constant : register(b0)
{
    unsigned int time;
}

VS_OUTPUT vsmain(VS_INPUT input_obj)
{
    VS_OUTPUT output_obj = (VS_OUTPUT) 0;
    
    output_obj.position = lerp(input_obj.position, input_obj.position1, (sin(time / 1000.0f) + 1.0f) / 2.0f);
    output_obj.color = input_obj.color;
    output_obj.color1 = input_obj.color1;
    return output_obj;
}