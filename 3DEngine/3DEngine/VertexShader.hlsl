struct VS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

VS_OUTPUT vsmain(VS_INPUT input_obj)
{
    VS_OUTPUT output_obj = (VS_OUTPUT) 0;
    
    output_obj.position = input_obj.position;
    output_obj.color = input_obj.color;
    
    return output_obj;
}