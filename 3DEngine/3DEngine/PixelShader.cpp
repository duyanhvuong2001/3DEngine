#include "PixelShader.h"
#include "GraphicsEngine.h"

PixelShader::PixelShader()
{
}

PixelShader::~PixelShader()
{
}

bool PixelShader::Init(const void* shader_byte_code, size_t shader_byte_code_length)
{
	//Get the DirectX Device from Graphics Engine to create a Vertex Shader
	if (!SUCCEEDED(GraphicsEngine::GetInstance()->m_d3d_device->CreatePixelShader(shader_byte_code, shader_byte_code_length, nullptr, &m_pixel_shader))) {
		return false;
	};
	return true;
}

void PixelShader::Release()
{
	m_pixel_shader->Release();
	delete this;
}
