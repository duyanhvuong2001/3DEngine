#pragma once
#include <memory>
#include "Vector3D.h"

class Matrix4x4
{
public:
	Matrix4x4() 
	{

	};
	~Matrix4x4()
	{

	};
public:
	void setIdentity();
	void setScale(const Vector3D& scale);
	void setTranslation(const Vector3D& vec);
	void setOrthoLH(float width, float height, float near_plane, float far_plane);

	//Operator modification
	void operator*=(const Matrix4x4& mat);
private:
	float m_matrix[4][4] = {};
};

