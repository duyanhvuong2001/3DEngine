#pragma once
#include <d3d11.h>
class SwapChain
{
public:
	SwapChain();
	//Initialize Swap Chain for a window
	bool Init(HWND hwnd, UINT width, UINT height);

	//Release Swap Chain
	bool Release();

	~SwapChain();
private:
	IDXGISwapChain* m_swap_chain;
};

