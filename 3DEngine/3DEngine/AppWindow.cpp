#include "AppWindow.h"
#include <Windows.h>
__declspec(align(16)) //Convert to a chain of 16-bytes
struct Constant {
	unsigned int time;
};


//Vector in 3D space
struct Vector3 {
	float x, y, z;
};


struct Vertex {
	Vector3 position;
	Vector3 position1;
	Vector3 color;
	Vector3 color1;
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
		{-0.5f,-0.5f,0.0f,     -0.32f, -0.11f, 0.0f,     1,0,0,		0,1,0}, //POS 1
		{-0.5f,0.5f,0.0f,      -0.11f, 0.78f, 0.0f,    0,1,0,		1,0,1}, //POS 2
		{0.5f,-0.5f,0.0f,      0.75f,-0.73f,0.0f,      0,0,1,		0,0.5,1}, //POS 3
		
		{0.5f,0.5f,0.0f,		0.88f,0.77f,0.0f,        1,1,0,		1,1,0.5}, //POS 4
		
		
	};

	m_vertex_buffer = GraphicsEngine::GetInstance()->CreateVertexBuffer();

	UINT size_vertex_list = ARRAYSIZE(vertex_list);

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;

	//Compile & Create Vertex Shader
	GraphicsEngine::GetInstance()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vertex_shader = GraphicsEngine::GetInstance()->CreateVertexShader(shader_byte_code, size_shader);
	

	m_vertex_buffer->Load(vertex_list, sizeof(Vertex), size_vertex_list, shader_byte_code, size_shader);

	//Release the compiled Shader
	GraphicsEngine::GetInstance()->ReleaseCompiledShader();

	//Compile & Create Pixel Shader
	GraphicsEngine::GetInstance()->CompilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_pixel_shader = GraphicsEngine::GetInstance()->CreatePixelShader(shader_byte_code, size_shader);

	//Release the compiled Shader
	GraphicsEngine::GetInstance()->ReleaseCompiledShader();

	//Create new constant obj
	Constant cons;
	cons.time = 0;

	//Create ConstantBuffer
	m_constant_buffer = GraphicsEngine::GetInstance()->CreateConstantBuffer();
	//Load the time attribute to the constant buffer
	m_constant_buffer->Load(&cons, sizeof(cons));

}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain,0, 0.4f, 0.2f, 1.0f);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//Create new constant
	Constant cons;
	cons.time = ::GetTickCount64();

	m_constant_buffer->Update(GraphicsEngine::GetInstance()->GetImmediateDeviceContext(), &cons);

	//Bind the constant buffer to the graphic pipeline
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetConstantBuffer(m_vertex_shader, m_constant_buffer);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetConstantBuffer(m_pixel_shader, m_constant_buffer);


	//Set the vertex shader for the device context
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexShader(m_vertex_shader);

	//Set the pixel shader for the device context
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetPixelShader(m_pixel_shader);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexBuffer(m_vertex_buffer);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawTriangleStrip(m_vertex_buffer->GetSizeVertexList(), 0);
	m_swap_chain->Present(true);
}

void AppWindow::OnDestroy()
{
	//Release all resources on destroy
	Window::OnDestroy();
	m_vertex_buffer->Release();
	m_swap_chain->Release();
	m_pixel_shader->Release();
	m_vertex_shader->Release();
	GraphicsEngine::GetInstance()->Release();
}
