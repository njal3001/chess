#pragma once
#include <ostream>

namespace Chess 
{
	struct Vec3
	{
		float x, y, z;

		Vec3();
		Vec3(const float x, const float y, const float z);

		Vec3 operator +(const Vec3& rhs) const;
		Vec3 operator -(const Vec3& rhs) const;
		Vec3 operator *(const Vec3& rhs) const;
		Vec3 operator /(const Vec3& rhs) const;
		Vec3 operator *(const float rhs) const;
		Vec3 operator /(const float rhs) const;

		Vec3& operator +=(const Vec3& rhs);
		Vec3& operator -=(const Vec3& rhs);
		Vec3& operator *=(const Vec3& rhs);
		Vec3& operator /=(const Vec3& rhs);
		Vec3& operator *=(const float rhs);
		Vec3& operator /=(const float rhs);

		bool operator ==(const Vec3& rhs) const;
		bool operator !=(const Vec3& rhs) const;

		friend std::ostream& operator <<(std::ostream& stream, const Vec3& vec);
	};
}

