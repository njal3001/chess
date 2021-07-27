#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <iostream>
#include "chess/utils/file.h"
#include "chess/maths/maths.h"

namespace Chess
{
	namespace Graphics
	{
		using namespace Maths;

		class Shader
		{
		private:
			GLuint m_shader_id;
			const char* m_vert_path;
			const char* m_frag_path;

		public:
			Shader(const char* vert_path, const char* frag_path);
			~Shader();

			void enable();
			void disable();

			void set_uniform_1f(const GLchar* name, float value);
			void set_uniform_1i(const GLchar* name, int value);
			void set_uniform_2f(const GLchar* name, const Vec2& vector);
			void set_uniform_3f(const GLchar* name, const Vec3& vector);
			void set_uniform_4f(const GLchar* name, const Vec4& vector);
			void set_uniform_mat4(const GLchar* name, const Mat4x4& matrix);

		private:
			GLuint load();
			GLint getUniformLocation(const GLchar* name);
		};

	}
}