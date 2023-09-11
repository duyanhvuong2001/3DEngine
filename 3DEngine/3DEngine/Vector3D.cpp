#include "Vector3D.h"

Vector3D::~Vector3D()
{
}

Vector3D Vector3D::Lerp(const Vector3D& start, const Vector3D& end, float delta)
{
	Vector3D vec;
	vec.m_x = start.m_x * (1.0f - delta) + end.m_x * delta;
	vec.m_y = start.m_y * (1.0f - delta) + end.m_y * delta;
	vec.m_z = start.m_z * (1.0f - delta) + end.m_z * delta;

	return vec;
}
