#include "DeviceContext.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context):m_device_context(device_context)
{

}

bool DeviceContext::Release()
{
	m_device_context->Release();
	return true;
}

DeviceContext::~DeviceContext()
{
}
