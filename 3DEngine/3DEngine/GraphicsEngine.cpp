#include "GraphicsEngine.h"
#include "SwapChain.h"
#include <d3dcompiler.h>
#include "VertexShader.h"
#include "PixelShader.h"

using namespace std;


GraphicsEngine* GraphicsEngine::GetInstance()
{
	static GraphicsEngine engine;
	return &engine;
}

GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::Init()
{
	//Declare driver types
	D3D_DRIVER_TYPE driver_types[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] = {
		D3D_FEATURE_LEVEL_11_0,

	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;

	
	for (UINT driver_type_idx = 0; driver_type_idx < num_driver_types;) {
		res = D3D11CreateDevice(NULL, driver_types[driver_type_idx],NULL,NULL,feature_levels,num_feature_levels,D3D11_SDK_VERSION,
			&m_d3d_device,//output device param
			&m_feature_level,//output feature level param
			&m_imm_context);

		if (SUCCEEDED(res)) {
			break;
		}
		++driver_type_idx;
	}

	if (FAILED(res)) {
		return false;
	}

	m_imm_device_context = new DeviceContext(m_imm_context);


	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);

	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);

	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}

bool GraphicsEngine::Release()
{
	

	m_d3d_device->Release();
	m_imm_device_context->Release();

	m_dxgi_adapter->Release();
	m_dxgi_device->Release();
	m_dxgi_factory->Release();
	return true;
}

SwapChain* GraphicsEngine::CreateSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::GetImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
	return new VertexBuffer();
}

VertexShader* GraphicsEngine::CreateVertexShader(const void* shader_byte_code, size_t shader_byte_code_length)
{
	VertexShader* vertex_shader = new VertexShader();
	if (!vertex_shader->Init(shader_byte_code, shader_byte_code_length)) {
		vertex_shader->Release();
		return nullptr;
	}

	return vertex_shader;
	
}

PixelShader* GraphicsEngine::CreatePixelShader(const void* shader_byte_code, size_t shader_byte_code_length)
{
	PixelShader* pixel_shader = new PixelShader();
	if (!pixel_shader->Init(shader_byte_code, shader_byte_code_length)) {
		pixel_shader->Release();
		return nullptr;
	}

	return pixel_shader;
}

bool GraphicsEngine::CompileVertexShader(const wchar_t* file_name,const char* entry_point_name,void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* err_blob = nullptr;
	//Compile from file from D3DCompile Lib
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &err_blob))) {
		if (err_blob)
		{
			err_blob->Release();
			return false;
		}
	}
	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();
	return true;
}

bool GraphicsEngine::CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* err_blob = nullptr;
	//Compile from file from D3DCompile Lib
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &err_blob))) {
		if (err_blob)
		{
			err_blob->Release();
			return false;
		}
	}
	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();
	return true;
}

void GraphicsEngine::ReleaseCompiledShader()
{
	//Release the blob containing shader codes
	if (m_blob) {
		m_blob->Release();
	}
}

GraphicsEngine::~GraphicsEngine()
{
}
