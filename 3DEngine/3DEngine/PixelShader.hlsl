struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};



float4 psmain(PS_INPUT input_obj) : SV_TARGET
{
	return float4(input_obj.color,1.0f);
}