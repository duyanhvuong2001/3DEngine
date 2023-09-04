#pragma once
#include <d3d11.h>
class GraphicsEngine;
class DeviceContext;

class VertexShader
{
public:
	VertexShader();
	~VertexShader();
private:
	bool Init(const void* shader_byte_code, size_t shader_byte_code_length);
	//The encapsulated DirectX shader
	ID3D11VertexShader* m_vertex_shader;
public:
	void Release();

	friend class GraphicsEngine;
	friend class DeviceContext;
};

