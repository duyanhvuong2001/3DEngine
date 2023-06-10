#pragma once
#include <d3d11.h>
#include "DeviceContext.h"
#include "VertexBuffer.h"

class SwapChain;
class VertexBuffer;

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

	~GraphicsEngine();
private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;

	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
	ID3D11DeviceContext* m_imm_context;

public:
	//Shaders methods
	bool CreateShaders();
	bool SetShaders();
	void GetShaderBufferAndSize(void** bytecode, UINT* size);
private:


	friend class SwapChain;
	friend class VertexBuffer;
private:
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;
private:
	DeviceContext* m_imm_device_context;
};

