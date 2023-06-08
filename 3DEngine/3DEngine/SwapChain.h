#pragma once
#include <d3d11.h>
class DeviceContext;
class SwapChain
{
public:
	SwapChain();
	//Initialize Swap Chain for a window
	bool Init(HWND hwnd, UINT width, UINT height);

	//Release Swap Chain
	bool Release();

	bool Present(bool vsync);

	~SwapChain();
private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_render_target_view;
	friend class DeviceContext;
};

