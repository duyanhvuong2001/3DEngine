#include "VertexBuffer.h"
#include "GraphicsEngine.h"
VertexBuffer::VertexBuffer()
{
}

bool VertexBuffer::Load(void* list_vertices, UINT size_vertex, UINT size_list)
{
	D3D11_BUFFER_DESC buffer_desc = {};

	buffer_desc.Usage = D3D11_USAGE_DEFAULT;//CPU & GPU are both able to write and read

	buffer_desc.ByteWidth = size_vertex*size_list; //Size in byte of buffer

	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	m_size_vertex = size_vertex;
	m_size_list = size_list;


	GraphicsEngine::GetInstance()->m_d3d_device->CreateBuffer(&buffer_desc,);
	return true;
}



bool VertexBuffer::Release()
{
	return true;
}

VertexBuffer::~VertexBuffer()
{
}
