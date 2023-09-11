#include "Matrix4x4.h"

void Matrix4x4::setIdentity()
{
	//Filling matrix with zeroes
	::memset(m_matrix, 0, sizeof(float)*16);

	//Set all values in the main diagonal to 1
	m_matrix[0][0] = 1;
	m_matrix[1][1] = 1;
	m_matrix[2][2] = 1;
	m_matrix[3][3] = 1;
}

void Matrix4x4::setScale(const Vector3D& scale)
{
	setIdentity();
	m_matrix[0][0] = scale.X();
	m_matrix[1][1] = scale.Y();
	m_matrix[2][2] = scale.Z();
}

void Matrix4x4::setTranslation(const Vector3D& vec)
{
	setIdentity();
	//Set all values in the last row to translation vector's coordinates
	m_matrix[3][0] = vec.X();
	m_matrix[3][1] = vec.Y();
	m_matrix[3][2] = vec.Z();
}



void Matrix4x4::setOrthoLH(float width, float height, float near_plane, float far_plane)
{
	setIdentity();
	m_matrix[0][0] = 2.0f / width;
	m_matrix[1][1] = 2.0f / height;
	m_matrix[2][2] = 1.0f / (far_plane - near_plane);
	m_matrix[3][2] = -(near_plane / (far_plane - near_plane));
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

