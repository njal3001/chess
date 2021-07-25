#include "vec3.h";
#include "calc.h";

namespace Chess 
{
	struct Mat4x4 
	{
		float values[4 * 4];

		Mat4x4();
		Mat4x4(float diagonal);

		static const Mat4x4 identity;

		Mat4x4 operator *(const Mat4x4& rhs);
		Mat4x4& operator *=(const Mat4x4& rhs);

		static Mat4x4 create_orthographic(float left, float right, float bottom, float top, float near, float far);
		static Mat4x4 create_perspective(float fov, float ratio, float near, float far);
		static Mat4x4 create_translation(const Vec3& trans);
		static Mat4x4 create_rotation(float angle, const Vec3& axis);
		static Mat4x4 create_scale(const Vec3& scale);
	};
}