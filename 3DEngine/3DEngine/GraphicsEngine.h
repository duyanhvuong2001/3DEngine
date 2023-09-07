#pragma once
#include <d3d11.h>
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"


class SwapChain;
class VertexBuffer;
class VertexShader;
class PixelShader;
class ConstantBuffer;

class GraphicsEngine
{
public:
	static GraphicsEngine* GetInstance();

	GraphicsEngine();
	//Initialize the graphics engine & DirectX 11 Device
	bool Init();

	//Release all loaded resources
	bool Release();


	//Self-implemented initializer
	SwapChain* CreateSwapChain();
	DeviceContext* GetImmediateDeviceContext();
	VertexBuffer* CreateVertexBuffer();
	ConstantBuffer* CreateConstantBuffer();
	VertexShader* CreateVertexShader(const void* shader_byte_code,size_t shader_byte_code_length);
	PixelShader* CreatePixelShader(const void* shader_byte_code, size_t shader_byte_code_length);
	~GraphicsEngine();
private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;

	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
	ID3D11DeviceContext* m_imm_context;

public:
	//Shaders Compilation
	bool CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void ReleaseCompiledShader();


private:

	//Friend classes can access private properties
	friend class SwapChain;
	friend class VertexBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class ConstantBuffer;
private:
	ID3DBlob* m_blob = nullptr;


	
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;
private:
	DeviceContext* m_imm_device_context;
};

