#include "VertexBuffer.h"
#include "GraphicsEngine.h"


VertexBuffer::VertexBuffer():m_input_layout(0),m_buffer(0)
{

}

bool VertexBuffer::Load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{
	//Release the previously loaded resources if new resources are about to be loaded
	if (m_buffer) {
		m_buffer->Release();
	}

	if (m_input_layout) {
		m_input_layout->Release();
	}

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

	//Create the vertex buffer
	HRESULT res = GraphicsEngine::GetInstance()->m_d3d_device->CreateBuffer(&buffer_desc,&init_data,&m_buffer);
	if (FAILED(res)) {
		
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		//SEMANTIC NAME - SEMANTIC IDX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA ,0}
	};

	//Get the number of attributes
	UINT size_of_layout = ARRAYSIZE(layout);

	//Create input layout which helps defining the attributes of the vertex type
	res = GraphicsEngine::GetInstance()->m_d3d_device->CreateInputLayout(layout,size_of_layout,shader_byte_code,size_byte_shader,&m_input_layout);

	if (FAILED(res)) {
		
		return false;
	}
	return true;
}

UINT VertexBuffer::GetSizeVertexList()
{
	return this->m_size_list;
}



bool VertexBuffer::Release()
{
	m_input_layout->Release();
	m_buffer->Release();
	delete this;
	return true;
}

VertexBuffer::~VertexBuffer()
{
}
