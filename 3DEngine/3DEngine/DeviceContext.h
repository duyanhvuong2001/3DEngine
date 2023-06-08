#pragma once
#include <d3d11.h>
class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool Release();
	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
};

