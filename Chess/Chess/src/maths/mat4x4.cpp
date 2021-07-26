#include "chess\maths\mat4x4.h"

namespace Chess 
{
	namespace Maths
	{
		Mat4x4::Mat4x4()
		{
			for (int i = 0; i < 4 * 4; i++)
				values[i] = 0.0f;
		}

		Mat4x4::Mat4x4(float diagonal)
		{
			for (int i = 0; i < 4 * 4; i++)
				values[i] = i % 5 ? 0.0f : diagonal;
		}

		const Mat4x4 Mat4x4::identity = Mat4x4(1.0f);

		Mat4x4 Mat4x4::operator*(const Mat4x4& rhs)
		{
			Mat4x4 res;

			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					float sum = 0.0f;
					for (int i = 0; i < 4; i++)
						sum += values[row + i * 4] * rhs.values[col * 4 + i];

					res.values[row + col * 4] = sum;
				}
			}

			return res;
		}

		Mat4x4& Mat4x4::operator*=(const Mat4x4& rhs)
		{
			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					float sum = 0.0f;
					for (int i = 0; i < 4; i++)
						sum += values[row + i * 4] * rhs.values[col * 4 + i];

					values[row + col * 4] = sum;
				}
			}

			return *this;
		}

		Mat4x4 Mat4x4::create_orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			Mat4x4 res = identity;
		
			res.values[0 + 0 * 4] = 2.0f / (right - left);
			res.values[0 + 3 * 4] = (right + left) / (right - left);
			res.values[1 + 1 * 4] = 2.0f / (top - bottom);
			res.values[1 + 3 * 4] = (top + bottom) / (top - bottom);
			res.values[2 + 2 * 4] = -2.0f / (far - near);
			res.values[2 + 3 * 4] = (far + near) / (far - near);

			return res;
		}

		Mat4x4 Mat4x4::create_perspective(float fov, float ratio, float near, float far)
		{
			Mat4x4 res;

			float q = 1.0f / tan(Calc::to_radians(fov) * 0.5f);

			res.values[0 + 0 * 4] = q / ratio;
			res.values[1 + 1 * 4] = q;
			res.values[2 + 2 * 4] = (-near - far) / (near - far);
			res.values[2 + 3 * 4] = (2 * far * near) / (near - far);
			res.values[3 + 2 * 4] = 1.0f;

			return res;
		}

		Mat4x4 Mat4x4::create_translation(const Vec3& trans)
		{
			Mat4x4 res = identity;

			res.values[0 + 3 * 4] = trans.x;
			res.values[1 + 3 * 4] = trans.y;
			res.values[2 + 3 * 4] = trans.z;

			return res;
		}

		Mat4x4 Mat4x4::create_rotation(float angle, const Vec3& axis)
		{
			Mat4x4 res = identity;

			float r = Calc::to_radians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			res.values[0 + 0 * 4] = c + x * x * omc;
			res.values[0 + 1 * 4] = x * y * omc - z * s;
			res.values[0 + 2 * 4] = x * z * omc + y * s;

			res.values[1 + 0 * 4] = y * x * omc + z * s;
			res.values[1 + 1 * 4] = c + y * y * omc;
			res.values[1 + 2 * 4] = y * z * omc - x * s;

			res.values[2 + 0 * 4] = z * x * omc - y * s;
			res.values[2 + 1 * 4] = z * y * omc + x * s;
			res.values[2 + 2 * 4] = c + z * z * omc;

			return res;
		}

		Mat4x4 Mat4x4::create_scale(const Vec3& scale)
		{
			Mat4x4 res = identity;

			res.values[0 + 0 * 4] = scale.x;
			res.values[1 + 1 * 4] = scale.y;
			res.values[2 + 2 * 4] = scale.z;

			return res;
		}
	}
}