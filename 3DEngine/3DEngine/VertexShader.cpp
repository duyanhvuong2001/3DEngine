#include "VertexShader.h"
#include "GraphicsEngine.h"

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
}

bool VertexShader::Init(const void* shader_byte_code,size_t shader_byte_code_length)
{
	//Get the DirectX Device from Graphics Engine to create a Vertex Shader
	if (!SUCCEEDED(GraphicsEngine::GetInstance()->m_d3d_device->CreateVertexShader(shader_byte_code, shader_byte_code_length, nullptr, &m_vertex_shader))) {
		return false;
	};
	return true;
}

void VertexShader::Release()
{
	m_vertex_shader->Release();
	delete this;
}
