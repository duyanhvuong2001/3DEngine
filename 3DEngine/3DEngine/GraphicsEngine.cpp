#include "GraphicsEngine.h"
#include "SwapChain.h"

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

	ID3D11DeviceContext* m_imm_context;
	
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

GraphicsEngine::~GraphicsEngine()
{
}
