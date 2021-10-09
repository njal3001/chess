#pragma once
#include <GL/glew.h>

namespace Game
{
	class IndexBuffer
	{
	private:
		GLuint m_buffer_id;
		GLuint m_count;

	public:
		IndexBuffer(GLushort* data, GLsizei count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		GLuint get_count() const;
	};
}