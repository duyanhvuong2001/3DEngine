#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context):m_device_context(device_context)
{

}

bool DeviceContext::Release()
{
	m_device_context->Release();
	delete this;
	return true;
}

void DeviceContext::ClearRenderTargetColor(SwapChain* swap_chain,float r, float g, float b, float a)
{
	FLOAT clear_color[] = {r,g,b,a};

	m_device_context->ClearRenderTargetView(swap_chain->m_render_target_view,clear_color);

	////Set render target we want to draw
	m_device_context->OMSetRenderTargets(1, &swap_chain->m_render_target_view, NULL);
}

void DeviceContext::SetVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex;
	UINT offset = 0;
	m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
	m_device_context->IASetInputLayout(vertex_buffer->m_input_layout);
}

void DeviceContext::DrawTriangleList(UINT vertex_count, UINT start_vertex_idx)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_device_context->Draw(vertex_count, start_vertex_idx);
	
	

}

void DeviceContext::DrawTriangleStrip(UINT vertex_count, UINT start_vertex_idx)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_device_context->Draw(vertex_count, start_vertex_idx);
}

void DeviceContext::SetViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;

	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_device_context->RSSetViewports(1, &vp);
}

DeviceContext::~DeviceContext()
{
}
