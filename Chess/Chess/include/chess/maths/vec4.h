#pragma once
#include <ostream>

namespace Chess 
{
	struct Vec4
	{
		float x, y, z, w;

		Vec4();
		Vec4(const float x, const float y, const float z, const float w);

		Vec4 operator +(const Vec4& rhs) const;
		Vec4 operator -(const Vec4& rhs) const;
		Vec4 operator *(const Vec4& rhs) const;
		Vec4 operator /(const Vec4& rhs) const;
		Vec4 operator *(const float rhs) const;
		Vec4 operator /(const float rhs) const;

		Vec4& operator +=(const Vec4& rhs);
		Vec4& operator -=(const Vec4& rhs);
		Vec4& operator *=(const Vec4& rhs);
		Vec4& operator /=(const Vec4& rhs);
		Vec4& operator *=(const float rhs);
		Vec4& operator /=(const float rhs);

		bool operator ==(const Vec4& rhs) const;
		bool operator !=(const Vec4& rhs) const;

		friend std::ostream& operator <<(std::ostream& stream, const Vec4& vec);
	};
}


