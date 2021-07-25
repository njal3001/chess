#include "chess/maths/vec2.h"

namespace Chess 
{
	Vec2::Vec2(): 
		x(0.0f), y(0.0f) {}

	Vec2::Vec2(const float x, const float y):
		x(x), y(y) {}

	Vec2 Vec2::operator +(const Vec2& rhs) const
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}

	Vec2 Vec2::operator -(const Vec2& rhs) const
	{
		return Vec2(x - rhs.x, y - rhs.y);
	}

	Vec2 Vec2::operator *(const Vec2& rhs) const
	{
		return Vec2(x * rhs.x, y * rhs.y);
	}

	Vec2 Vec2::operator /(const Vec2& rhs) const
	{
		return Vec2(x / rhs.x, y / rhs.y);
	}

	Vec2 Vec2::operator *(const float rhs) const
	{
		return Vec2(x * rhs, y * rhs);
	}

	Vec2 Vec2::operator /(const float rhs) const
	{
		return Vec2(x / rhs, y / rhs);
	}

	Vec2& Vec2::operator +=(const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vec2& Vec2::operator -=(const Vec2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vec2& Vec2::operator *=(const Vec2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	Vec2& Vec2::operator /=(const Vec2& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	Vec2& Vec2::operator *=(const float rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vec2& Vec2::operator/=(const float rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	bool Vec2::operator==(const Vec2& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool Vec2::operator!=(const Vec2& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}

	std::ostream& operator <<(std::ostream& stream, const Vec2& vec)
	{
		stream << "(" << vec.x << "," << vec.y << ")";
		return stream;
	}
}