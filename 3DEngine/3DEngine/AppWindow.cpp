#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"

//Convert to a chain of 16-bytes
__declspec(align(16)) 
struct Constant {
	
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection;
	unsigned int m_time;
};


//Vector in 3D space



struct Vertex {
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
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
		{Vector3D(-0.5f,-0.5f,0.0f),	Vector3D(-0.32f, -0.11f, 0.0f),		Vector3D(1,0,0),		Vector3D(0,1,0)}, //POS 1
		{Vector3D(-0.5f,0.5f,0.0f),		Vector3D(-0.11f, 0.78f, 0.0f),		Vector3D(0,1,0),		Vector3D(1,0,1)}, //POS 2
		{Vector3D(0.5f,-0.5f,0.0f),		Vector3D(0.75f,-0.73f,0.0f),		Vector3D(0,0,1),		Vector3D(0,0.5f,1)}, //POS 3
		{Vector3D(0.5f,0.5f,0.0f),		Vector3D(0.88f,0.77f,0.0f),			Vector3D(1,1,0),		Vector3D(1,1,0.5)} //POS 4
		
		
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
	cons.m_time = 0;

	//Create ConstantBuffer
	m_constant_buffer = GraphicsEngine::GetInstance()->CreateConstantBuffer();
	//Load the m_time attribute to the constant buffer
	m_constant_buffer->Load(&cons, sizeof(cons));

}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain,0, 0.4f, 0.3f, 1.0f);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//Update quad position
	UpdateQuadPosition();

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
	
	//Update old delta
	m_delta_old = m_delta_new;

	//Get new delta
	m_delta_new = ::GetTickCount64();

	//Calculate delta time
	m_delta_time = (m_delta_old)?((m_delta_new - m_delta_old)/1000.0f):0;
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

void AppWindow::UpdateQuadPosition()
{
	//Create new constant
	Constant cons;

	//Get the runtime current tick
	cons.m_time = ::GetTickCount64();

	m_delta_pos += m_delta_time * 0.8f;
	
	//if (m_delta_pos > 1.0f) {
	//	m_delta_pos = 0;
	//}

	////Set translate
	//cons.m_world.setTranslation(Vector3D::Lerp(Vector3D(0,-2,0),Vector3D(0,3,0),m_delta_pos));

	
	//Set scale
	m_delta_scale += m_delta_time * 0.4f;
	Matrix4x4 temp;
	cons.m_world.setScale(Vector3D::Lerp(Vector3D(1, 1, 0), Vector3D(2, 2, 0), (sin(m_delta_scale)+1)/2.0f));

	
	temp.setTranslation(Vector3D::Lerp(Vector3D(0, 0, 0), Vector3D(0, 1, 0), (sin(m_delta_pos) + 1) / 2.0f));

	cons.m_world *= temp;

	//Set view matrix
	cons.m_view.setIdentity();

	//Set projection matrix
	RECT clientWindow = this->GetClientWindowRect();

	cons.m_projection.setOrthoLH(
		(clientWindow.right - clientWindow.left)/400.0f,
		(clientWindow.bottom - clientWindow.top)/400.0f, 
		-4.0f, 
		4.0f);

	m_constant_buffer->Update(GraphicsEngine::GetInstance()->GetImmediateDeviceContext(), &cons);
}
