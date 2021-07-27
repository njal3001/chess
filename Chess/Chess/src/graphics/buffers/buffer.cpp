#include "chess/graphics/buffers/buffer.h"

namespace Chess
{
	namespace Graphics
	{
		Buffer::Buffer(GLfloat* data, GLsizei count, GLuint component_count)
			: m_component_count(component_count)
		{
			glGenBuffers(1, &m_buffer_id);
			bind();
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
			unbind();
		}

		void Buffer::bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
		}

		void Buffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		GLuint Buffer::get_component_count() const
		{
			return m_component_count;
		}
	}
}