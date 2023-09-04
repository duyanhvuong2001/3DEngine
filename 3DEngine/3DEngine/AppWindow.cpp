#include "AppWindow.h"

//Vector in 3D space
struct Vector3 {
	float x, y, z;
};


struct Vertex {
	Vector3 position;
};


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

	Vertex vertex_list[] = 
	{
		{-0.5f,-0.5f,0.0f}, //POS 1
		{-0.5f,0.5f,0.0f}, //POS 2
		{0.5f,-0.5f,0.0f}, //POS 3
		
		{0.5f,0.5f,0.0f}, //POS 4
		
		
	};

	m_vertex_buffer = GraphicsEngine::GetInstance()->CreateVertexBuffer();

	UINT size_vertex_list = ARRAYSIZE(vertex_list);

	//Create shaders
	GraphicsEngine::GetInstance()->CreateShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;

	GraphicsEngine::GetInstance()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vertex_shader = GraphicsEngine::GetInstance()->CreateVertexShader(shader_byte_code, size_shader);


	m_vertex_buffer->Load(vertex_list, sizeof(Vertex), size_vertex_list, shader_byte_code, size_shader);

	//Release the compiled VS
	GraphicsEngine::GetInstance()->ReleaseCompiledShader();

}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain,0, 0.4f, 0.2f, 1.0f);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::GetInstance()->SetShaders();

	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexShader(m_vertex_shader);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexBuffer(m_vertex_buffer);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawTriangleStrip(m_vertex_buffer->GetSizeVertexList(), 0);
	m_swap_chain->Present(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	m_vertex_buffer->Release();
	m_swap_chain->Release();
	GraphicsEngine::GetInstance()->Release();
}
