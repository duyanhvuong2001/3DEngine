#pragma once
class VertexBuffer
{
public:
	VertexBuffer();
	bool Load(void* list_vertices,UINT size_vertex,UINT size_list);
	bool Release();
	~VertexBuffer();
private:
	UINT m_size_vertex;
	UINT m_size_list;
};

