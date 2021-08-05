#include "chess/graphics/shader.h";

namespace Chess 
{
	namespace Graphics
	{
		Shader::Shader(const char* vert_path, const char* frag_path)
			: m_vert_path(vert_path), m_frag_path(frag_path)
		{
			m_shader_id = load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_shader_id);
		}

		GLuint Shader::load()
		{
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vert_source_str = Utils::read_file(m_vert_path);
			std::string frag_source_str = Utils::read_file(m_frag_path);

			const char* vert_source = vert_source_str.c_str();
			const char* frag_source = frag_source_str.c_str();

			glShaderSource(vertex, 1, &vert_source, NULL);
			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);

				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);

				std::cout << "Failed to compile vertex shader!" << std::endl <<
					&error[0] << std::endl;

				glDeleteShader(vertex);
				return 0;
			}

			glShaderSource(fragment, 1, &frag_source, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);

				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);

				std::cout << "Failed to compile fragment shader!" << std::endl <<
					&error[0] << std::endl;

				glDeleteShader(vertex);
				glDeleteShader(fragment);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		void Shader::enable()
		{
			glUseProgram(m_shader_id);
		}

		void Shader::disable()
		{
			glUseProgram(0);
		}

		GLint Shader::getUniformLocation(const GLchar* name)
		{
			if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
				return m_uniform_location_cache[name];

			GLint location = glGetUniformLocation(m_shader_id, name);
			m_uniform_location_cache[name] = location;

			return location;
		}

		void Shader::set_uniform_1f(const GLchar* name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::set_uniform_1i(const GLchar* name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::set_uniform_2f(const GLchar* name, const Maths::Vec2& vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::set_uniform_3f(const GLchar* name, const Maths::Vec3& vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::set_uniform_4f(const GLchar* name, const Maths::Vec4& vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::set_uniform_mat4(const GLchar* name, const Maths::Mat4x4& matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.values);
		}

	}
}