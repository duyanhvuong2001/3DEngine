
#include "SwapChain.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain()
{
}

bool SwapChain::Init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::GetInstance()->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;

	//Fill the initial values of the desc with 0s
	ZeroMemory(&desc, sizeof(desc));

	desc.BufferCount = 1; //only 1 buffer needed because the other one is the Window itself
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;

	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;
	//Create the swap chain using the DXGI factory, indicated by HWND parameters
	HRESULT res = GraphicsEngine::GetInstance()->m_dxgi_factory->CreateSwapChain(device,&desc,&m_swap_chain);
	if (FAILED(res)) {
		return false;
	}

	//Get the back buffer color & create its render target view
	ID3D11Texture2D* buffer = NULL;

	res = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(res)) {
		
		return false;
	}

	res = device->CreateRenderTargetView(buffer, NULL, &m_render_target_view);

	if (FAILED(res)) {
		
		return false;
	}

	return true;
}

bool SwapChain::Release()
{
	m_swap_chain->Release();
	delete this;
	return true;
}

bool SwapChain::Present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);

	return true;
}

SwapChain::~SwapChain()
{

}
