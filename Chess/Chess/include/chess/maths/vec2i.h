#pragma once
#include <ostream>

namespace Chess 
{
	namespace Maths
	{
		struct Vec2i
		{
			int x, y;

			Vec2i();
			Vec2i(const int x, const int y);

			Vec2i operator +(const Vec2i& rhs) const;
			Vec2i operator -(const Vec2i& rhs) const;
			Vec2i operator *(const Vec2i& rhs) const;
			Vec2i operator /(const Vec2i& rhs) const;
			Vec2i operator *(const int rhs) const;
			Vec2i operator /(const int rhs) const;

			Vec2i& operator +=(const Vec2i& rhs);
			Vec2i& operator -=(const Vec2i& rhs);
			Vec2i& operator *=(const Vec2i& rhs);
			Vec2i& operator /=(const Vec2i& rhs);
			Vec2i& operator *=(const int rhs);
			Vec2i& operator /=(const int rhs);

			bool operator ==(const Vec2i& rhs) const;
			bool operator !=(const Vec2i& rhs) const;

			friend std::ostream& operator <<(std::ostream& stream, const Vec2i& vec);
		};
	}
}
