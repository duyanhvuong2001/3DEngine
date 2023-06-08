#include "Window.h"
Window::Window() 
{

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) 
	{
	case WM_CREATE:
	{


		// Event fired when the window is created
		// collected here..
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		// .. and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->setHWND(hwnd);
		window->OnCreate();
		break;
	}

	case WM_DESTROY: 
	{//Event fired when window is destroyed
		// Event fired when the window is destroyed
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->OnDestroy();
		::PostQuitMessage(0);
		break;
	}
	default: {

		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
	}

	return NULL;
}

bool Window::Init()
{
	//Setting up WNDCLASSEX obj
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";

	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;
	

	if (!::RegisterClassEx(&wc)) // If the registration of class will fail, the function will return false
		return false;
	

	//Create window
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"Duy Anh iu Quynh Anh Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, this);
	//If creation fails

	if (!m_hwnd) {

		return false;
	}

	//Else show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	

	//Set the running flag
	m_is_running = true;

	return true;


}

bool Window::Broadcast()
{
	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	this->OnUpdate();

	Sleep(1);

	return true;
}

bool Window::Release()
{
	//Destroy the window
	if (!::DestroyWindow(m_hwnd)) {
		return false;
	}
	return true;
}

bool Window::isRunning()
{
	return m_is_running;
}

RECT Window::GetClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::OnCreate()
{
}

void Window::OnUpdate()
{
}

void Window::OnDestroy()
{
	//set the running flag to false
	m_is_running = false;
}

Window::~Window()
{
}
