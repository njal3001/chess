#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <iostream>
#include "chess/utils/file.h"
#include "chess/maths/maths.h"
#include <unordered_map>

namespace Game
{
	class Shader
	{
	private:
		GLuint m_shader_id;
		const char* m_vert_path;
		const char* m_frag_path;
		std::unordered_map<std::string, GLint> m_uniform_location_cache;

	public:
		Shader(const char* vert_path, const char* frag_path);
		~Shader();

		void enable();
		void disable();

		void set_uniform_1f(const GLchar* name, float value);
		void set_uniform_1i(const GLchar* name, int value);
		void set_uniform_1iv(const GLchar* name, int* value, int count);
		void set_uniform_2f(const GLchar* name, const Vec2& vector);
		void set_uniform_3f(const GLchar* name, const Vec3& vector);
		void set_uniform_4f(const GLchar* name, const Vec4& vector);
		void set_uniform_mat4(const GLchar* name, const Mat4x4& matrix);

	private:
		GLuint load();
		GLint get_uniform_location(const GLchar* name);
	};

}
