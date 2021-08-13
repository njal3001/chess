#include "chess/graphics/buffers/indexbuffer.h"

namespace Chess
{
	namespace Graphics
	{
		IndexBuffer::IndexBuffer(GLushort* data, GLsizei count)
			: m_count(count)
		{
			glGenBuffers(1, &m_buffer_id);
			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			unbind();
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &m_buffer_id);
		}

		void IndexBuffer::bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id);
		}

		void IndexBuffer::unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		GLuint IndexBuffer::get_count() const
		{
			return m_count;
		}
	}
}
