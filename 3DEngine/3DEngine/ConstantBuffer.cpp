#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
ConstantBuffer::ConstantBuffer()
{
}
bool ConstantBuffer::Load(void* buffer, UINT size_of_buffer)
{
	//Release the previously loaded resources if new resources are about to be loaded
	if (m_buffer) {
		m_buffer->Release();
	}

	D3D11_BUFFER_DESC buffer_desc = {};

	buffer_desc.Usage = D3D11_USAGE_DEFAULT;//CPU & GPU are both able to write and read
	buffer_desc.ByteWidth = size_of_buffer;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;

	//Create the vertex buffer
	HRESULT res = GraphicsEngine::GetInstance()->m_d3d_device->CreateBuffer(&buffer_desc, &init_data, &m_buffer);
	if (FAILED(res)) {

		return false;
	}

	
	return true;
}

void ConstantBuffer::Update(DeviceContext* device_context, void* buffer)
{
	//Upload new data into video memory via device context
	device_context->m_device_context->UpdateSubresource(m_buffer, NULL, NULL, buffer, NULL,NULL);
}

bool ConstantBuffer::Release()
{
	m_buffer->Release();
	delete this;
	return true;
}

ConstantBuffer::~ConstantBuffer()
{
}
