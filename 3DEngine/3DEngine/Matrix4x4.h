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
	void SetIdentity();
	void SetScale(const Vector3D& scale);
	void SetTranslation(const Vector3D& vec);
	void SetOrthoLH(float width, float height, float near_plane, float far_plane);
	
	void SetRotationX(float phi);
	void SetRotationY(float phi);
	void SetRotationZ(float phi);
	//Operator modification
	void operator*=(const Matrix4x4& mat);
private:
	float m_matrix[4][4] = {};
};

