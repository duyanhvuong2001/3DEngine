#include "IndexBuffer.h"
#include "GraphicsEngine.h"

const size_t SIZE_OF_VERTEX = 4;

IndexBuffer::IndexBuffer():m_buffer(0)
{
}

bool IndexBuffer::Load(void* list_indices, UINT size_list)
{
	if (m_buffer) {
		m_buffer->Release();
	}
	D3D11_BUFFER_DESC buffer_desc = {};

	buffer_desc.Usage = D3D11_USAGE_DEFAULT;//CPU & GPU are both able to write and read
	buffer_desc.ByteWidth = SIZE_OF_VERTEX * size_list;
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_indices;

	m_size_list = size_list;

	//Create the index buffer
	HRESULT res = GraphicsEngine::GetInstance()->m_d3d_device->CreateBuffer(&buffer_desc, &init_data, &m_buffer);
	if (FAILED(res)) {

		return false;
	}


	return true;
}

UINT IndexBuffer::GetSizeIndexList()
{
	return m_size_list;
}

bool IndexBuffer::Release()
{
	m_buffer->Release();
	delete this;
	return true;
}

IndexBuffer::~IndexBuffer()
{
}
