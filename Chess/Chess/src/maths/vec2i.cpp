
#include "chess/maths/vec2i.h"

namespace Game 
{
	Vec2i::Vec2i(): 
		x(0), y(0) {}

	Vec2i::Vec2i(const int x, const int y):
		x(x), y(y) {}

	Vec2i Vec2i::operator +(const Vec2i& rhs) const
	{
		return Vec2i(x + rhs.x, y + rhs.y);
	}

	Vec2i Vec2i::operator -(const Vec2i& rhs) const
	{
		return Vec2i(x - rhs.x, y - rhs.y);
	}

	Vec2i Vec2i::operator *(const Vec2i& rhs) const
	{
		return Vec2i(x * rhs.x, y * rhs.y);
	}

	Vec2i Vec2i::operator /(const Vec2i& rhs) const
	{
		return Vec2i(x / rhs.x, y / rhs.y);
	}

	Vec2i Vec2i::operator *(const int rhs) const
	{
		return Vec2i(x * rhs, y * rhs);
	}

	Vec2i Vec2i::operator /(const int rhs) const
	{
		return Vec2i(x / rhs, y / rhs);
	}

	Vec2i& Vec2i::operator +=(const Vec2i& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vec2i& Vec2i::operator -=(const Vec2i& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vec2i& Vec2i::operator *=(const Vec2i& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	Vec2i& Vec2i::operator /=(const Vec2i& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	Vec2i& Vec2i::operator *=(const int rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vec2i& Vec2i::operator/=(const int rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	bool Vec2i::operator==(const Vec2i& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool Vec2i::operator!=(const Vec2i& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}

	std::ostream& operator <<(std::ostream& stream, const Vec2i& vec)
	{
		stream << "(" << vec.x << "," << vec.y << ")";
		return stream;
	}
}