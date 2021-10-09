#include "chess/maths/Vec3.h"

namespace Game 
{
	Vec3::Vec3() :
		x(0.0f), y(0.0f), z(0.0f) {}

	Vec3::Vec3(const float x, const float y, const float z) :
		x(x), y(y), z(z) {}

	Vec3 Vec3::operator +(const Vec3& rhs) const
	{
		return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vec3 Vec3::operator -(const Vec3& rhs) const
	{
		return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vec3 Vec3::operator *(const Vec3& rhs) const
	{
		return Vec3(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	Vec3 Vec3::operator /(const Vec3& rhs) const
	{
		return Vec3(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	Vec3 Vec3::operator *(const float rhs) const
	{
		return Vec3(x * rhs, y * rhs, z * rhs);
	}

	Vec3 Vec3::operator /(const float rhs) const
	{
		return Vec3(x / rhs, y / rhs, z / rhs);
	}

	Vec3& Vec3::operator +=(const Vec3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vec3& Vec3::operator -=(const Vec3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vec3& Vec3::operator *=(const Vec3& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	Vec3& Vec3::operator /=(const Vec3& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	Vec3& Vec3::operator *=(const float rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	Vec3& Vec3::operator/=(const float rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	bool Vec3::operator==(const Vec3& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	bool Vec3::operator!=(const Vec3& rhs) const
	{
		return x != rhs.x || y != rhs.y || z != rhs.z;
	}

	std::ostream& operator <<(std::ostream& stream, const Vec3& vec)
	{
		stream << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
		return stream;
	}
}