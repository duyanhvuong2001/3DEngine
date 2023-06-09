#pragma once
#include <d3d11.h>
class SwapChain;
class VertexBuffer;
class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool Release();
	void ClearRenderTargetColor(SwapChain* swap_chain, float r, float g, float b, float a);
	void SetVertexBuffer(VertexBuffer* vertex_buffer);
	void DrawTriangleList(UINT vertex_count, UINT start_vertex_idx);
	void DrawTriangleStrip(UINT vertex_count, UINT start_vertex_idx);
	void SetViewportSize(UINT width, UINT height);
	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
};

