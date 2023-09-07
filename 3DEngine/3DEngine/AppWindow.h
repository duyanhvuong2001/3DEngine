#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"


class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;
private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vertex_buffer;
	VertexShader* m_vertex_shader;
	PixelShader* m_pixel_shader;
	ConstantBuffer* m_constant_buffer;
};

