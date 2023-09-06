#pragma once
#include <d3d11.h>
class GraphicsEngine;
class DeviceContext;

class PixelShader
{
public:
	PixelShader();
	~PixelShader();
private:
	bool Init(const void* shader_byte_code, size_t shader_byte_code_length);
	//The encapsulated DirectX shader
	ID3D11PixelShader* m_pixel_shader;
public:
	void Release();

	friend class GraphicsEngine;
	friend class DeviceContext;
};
