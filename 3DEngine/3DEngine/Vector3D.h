#pragma once
class Vector3D
{
private:
	float m_x, m_y, m_z;
public:
	//Default constructors
	Vector3D() :m_x(0), m_y(0), m_z(0) {

	};

	Vector3D(float x, float y, float z) :m_x(x), m_y(y), m_z(z) {

	};

	//Copy vector
	Vector3D(const Vector3D& vec) : m_x(vec.m_x), m_y(vec.m_y), m_z(vec.m_z) {

	};

	float X() const noexcept { return m_x; };
	float Y() const noexcept { return m_y; };
	float Z() const noexcept { return m_z; };

	~Vector3D();

	static Vector3D Lerp(const Vector3D& start, const Vector3D& end, float delta);
};

