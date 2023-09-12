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
		//X - Y - Z
		//Front face vertices
		{Vector3D(-0.5f,-0.5f,-0.5f),			Vector3D(1,0,0),		Vector3D(0,1,0)}, //IDX 0
		{Vector3D(-0.5f,0.5f,-0.5f),				Vector3D(0,1,0),		Vector3D(1,0,1)}, //IDX 1
		{Vector3D(0.5f,0.5f,-0.5f),				Vector3D(0,0,1),		Vector3D(0,0.5f,1)}, //IDX 2
		{Vector3D(0.5f,-0.5f,-0.5f),				Vector3D(1,1,0),		Vector3D(1,1,0.5)}, //IDX 3

		//Rear face vertices
		{Vector3D(0.5f,-0.5f,0.5f),				Vector3D(1,1,0),		Vector3D(1,1,0.5)}, //IDX 4
		{Vector3D(0.5f,0.5f,0.5f),				Vector3D(1,1,0),		Vector3D(1,1,0.5)}, //IDX 5
		{Vector3D(-0.5f,0.5f,0.5f),				Vector3D(1,1,0),		Vector3D(1,1,0.5)},//IDX 6
		{Vector3D(-0.5f,-0.5f,0.5f),				Vector3D(1,1,0),		Vector3D(1,1,0.5)} //IDX 7
		
		
	};

	m_vertex_buffer = GraphicsEngine::GetInstance()->CreateVertexBuffer();

	UINT size_vertex_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] = {
		//FRONT SIDE
		0,1,2,	//1ST TRIANGLE
		2,3,0,	//2ND TRIANGLE
		//REAR SIDE
		4,5,6, 
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	m_index_buffer = GraphicsEngine::GetInstance()->CreateIndexBuffer();

	UINT size_index_list = ARRAYSIZE(index_list);

	m_index_buffer->Load(index_list, size_index_list);


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

	//Set the index buffer for rendering triangles
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetIndexBuffer(m_index_buffer);
	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawIndexedTriangleList(m_index_buffer->GetSizeIndexList(), 0, 0);
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
	m_constant_buffer->Release();
	m_index_buffer->Release();
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

	//Set delta position
	m_delta_pos += m_delta_time * 0.8f;

	//Set delta scale
	m_delta_scale += m_delta_time * 0.4f;


	//World matrix operations
	cons.m_world.SetScale(Vector3D(1, 1, 1));

	Matrix4x4 temp;

	temp.SetRotationZ(m_delta_scale);

	cons.m_world *= temp;

	temp.SetRotationY(m_delta_scale);

	cons.m_world *= temp;

	temp.SetRotationX(m_delta_scale);

	cons.m_world *= temp;

	//cons.m_world.setScale(Vector3D::Lerp(Vector3D(1, 1, 0), Vector3D(2, 2, 0), (sin(m_delta_scale)+1)/2.0f));

	//
	//temp.setTranslation(Vector3D::Lerp(Vector3D(-1, -1, 0), Vector3D(0, 1, 0), (sin(m_delta_pos) + 1) / 2.0f));

	//cons.m_world *= temp;



	//View matrix operations
	cons.m_view.SetIdentity();

	//Set projection matrix
	RECT clientWindow = this->GetClientWindowRect();

	cons.m_projection.SetOrthoLH(
		(clientWindow.right - clientWindow.left)/200.0f,
		(clientWindow.bottom - clientWindow.top)/200.0f, 
		-4.0f, 
		4.0f);

	m_constant_buffer->Update(GraphicsEngine::GetInstance()->GetImmediateDeviceContext(), &cons);
}
