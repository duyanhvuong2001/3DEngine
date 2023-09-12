struct VS_INPUT
{
    float4 position : POSITION;
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
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_projection;
    unsigned int m_time;
}

VS_OUTPUT vsmain(VS_INPUT input_obj)
{
    VS_OUTPUT output_obj = (VS_OUTPUT) 0;
    output_obj.position = input_obj.position;

    //Transform to world space
    output_obj.position = mul(output_obj.position, m_world);
    
    //Transform to window space
    output_obj.position = mul(output_obj.position, m_view);
    
    //Transform to viewport space (range -1 to 1
    output_obj.position = mul(output_obj.position, m_projection);
    
    
    //output_obj.position = lerp(input_obj.position, input_obj.position1, (sin(time / 1000.0f) + 1.0f) / 2.0f);
    output_obj.color = input_obj.color;
    output_obj.color1 = input_obj.color1;
    return output_obj;
}