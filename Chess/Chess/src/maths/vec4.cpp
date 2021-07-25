#include "chess/maths/Vec4.h"

namespace Chess {

	Vec4::Vec4() :
		x(0), y(0), z(0), w(0) {}

	Vec4::Vec4(const float x, const float y, const float z, const float w) :
		x(x), y(y), z(z), w(w) {}

	Vec4 Vec4::operator +(const Vec4& rhs) const
	{
		return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	Vec4 Vec4::operator -(const Vec4& rhs) const
	{
		return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	Vec4 Vec4::operator *(const Vec4& rhs) const
	{
		return Vec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
	}

	Vec4 Vec4::operator /(const Vec4& rhs) const
	{
		return Vec4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
	}

	Vec4 Vec4::operator *(const float rhs) const
	{
		return Vec4(x * rhs, y * rhs, z * rhs, w * rhs);
	}

	Vec4 Vec4::operator /(const float rhs) const
	{
		return Vec4(x / rhs, y / rhs, z / rhs, w / rhs);
	}

	Vec4& Vec4::operator +=(const Vec4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	Vec4& Vec4::operator -=(const Vec4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	Vec4& Vec4::operator *=(const Vec4& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}

	Vec4& Vec4::operator /=(const Vec4& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;
		return *this;
	}

	Vec4& Vec4::operator *=(const float rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	Vec4& Vec4::operator/=(const float rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;
		return *this;
	}

	bool Vec4::operator==(const Vec4& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}

	bool Vec4::operator!=(const Vec4& rhs) const
	{
		return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
	}

	std::ostream& operator <<(std::ostream& stream, const Vec4& vec)
	{
		stream << "(" << vec.x << "," << vec.y << "," << vec.z << "," << vec.w << ")";
		return stream;
	}
}