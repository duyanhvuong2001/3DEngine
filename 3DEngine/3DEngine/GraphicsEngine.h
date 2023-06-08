#pragma once
#include <d3d11.h>
#include "DeviceContext.h"

class SwapChain;

class GraphicsEngine
{
public:
	static GraphicsEngine* GetInstance();

	GraphicsEngine();
	//Initialize the graphics engine & DirectX 11 Device
	bool Init();

	//Release all loaded resources
	bool Release();

	SwapChain* CreateSwapChain();
	DeviceContext* GetImmediateDeviceContext();

	~GraphicsEngine();
private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;

	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
private:
	friend class SwapChain;
private:
	DeviceContext* m_imm_device_context;
};

