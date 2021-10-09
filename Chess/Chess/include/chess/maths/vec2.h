#pragma once
#include <ostream>

namespace Game 
{
	struct Vec2 
	{
		float x, y;

		Vec2();
		Vec2(const float x, const float y);

		Vec2 operator +(const Vec2& rhs) const;
		Vec2 operator -(const Vec2& rhs) const;
		Vec2 operator *(const Vec2& rhs) const;
		Vec2 operator /(const Vec2& rhs) const;
		Vec2 operator *(const float rhs) const;
		Vec2 operator /(const float rhs) const;

		Vec2& operator +=(const Vec2& rhs);
		Vec2& operator -=(const Vec2& rhs);
		Vec2& operator *=(const Vec2& rhs);
		Vec2& operator /=(const Vec2& rhs);
		Vec2& operator *=(const float rhs);
		Vec2& operator /=(const float rhs);

		bool operator ==(const Vec2& rhs) const;
		bool operator !=(const Vec2& rhs) const;

		friend std::ostream& operator <<(std::ostream& stream, const Vec2& vec);
	};
}
