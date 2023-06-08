#include "AppWindow.h"

AppWindow::AppWindow()
{
	

}

AppWindow::~AppWindow()
{
}

void AppWindow::OnCreate()
{
	Window::OnCreate();
	GraphicsEngine::GetInstance()->Init();
	m_swap_chain = GraphicsEngine::GetInstance()->CreateSwapChain();

	RECT rc = this->GetClientWindowRect();
	m_swap_chain->Init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain, 1, 0, 0, 1);

	m_swap_chain->Present(false);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();

	m_swap_chain->Release();
	GraphicsEngine::GetInstance()->Release();
}
