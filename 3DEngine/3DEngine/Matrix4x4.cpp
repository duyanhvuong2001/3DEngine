#include "Matrix4x4.h"

void Matrix4x4::SetIdentity()
{
	//Filling matrix with zeroes
	::memset(m_matrix, 0, sizeof(float)*16);

	//Set all values in the main diagonal to 1
	m_matrix[0][0] = 1;
	m_matrix[1][1] = 1;
	m_matrix[2][2] = 1;
	m_matrix[3][3] = 1;
}

void Matrix4x4::SetScale(const Vector3D& scale)
{
	SetIdentity();
	m_matrix[0][0] = scale.X();
	m_matrix[1][1] = scale.Y();
	m_matrix[2][2] = scale.Z();
}

void Matrix4x4::SetTranslation(const Vector3D& vec)
{
	SetIdentity();
	//Set all values in the last row to translation vector's coordinates
	m_matrix[3][0] = vec.X();
	m_matrix[3][1] = vec.Y();
	m_matrix[3][2] = vec.Z();
}



void Matrix4x4::SetOrthoLH(float width, float height, float near_plane, float far_plane)
{
	SetIdentity();
	m_matrix[0][0] = 2.0f / width;
	m_matrix[1][1] = 2.0f / height;
	m_matrix[2][2] = 1.0f / (far_plane - near_plane);
	m_matrix[3][2] = -(near_plane / (far_plane - near_plane));
}

void Matrix4x4::SetRotationX(float phi)
{
	SetIdentity();
	m_matrix[1][1] = cos(phi);
	m_matrix[1][2] = sin(phi);
	m_matrix[2][1] = -sin(phi);
	m_matrix[2][2] = cos(phi);
}

void Matrix4x4::SetRotationY(float phi)
{
	SetIdentity();
	m_matrix[0][0] = cos(phi);
	m_matrix[0][1] = sin(phi);
	m_matrix[1][0] = -sin(phi);
	m_matrix[1][1] = cos(phi);

}

void Matrix4x4::SetRotationZ(float phi)
{
	SetIdentity();
	m_matrix[0][0] = cos(phi);
	m_matrix[0][2] = -sin(phi);
	m_matrix[2][0] = sin(phi);
	m_matrix[2][2] = cos(phi);
}

void Matrix4x4::operator*=(const Matrix4x4& other_mat)
{
	Matrix4x4 result;
	for (int i=0; i < 4; i++) {
		for (int j=0; j < 4; j++) {
			result.m_matrix[i][j] = m_matrix[i][0] * other_mat.m_matrix[0][j]
				+ m_matrix[i][1] * other_mat.m_matrix[1][j]
				+ m_matrix[i][2] * other_mat.m_matrix[2][j]
				+ m_matrix[i][3] * other_mat.m_matrix[3][j];
		}
	}
	::memcpy(m_matrix, result.m_matrix, sizeof(float) * 16);
}

