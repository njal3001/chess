#include "chess/graphics/buffers/buffer.h"

namespace Chess
{
	namespace Graphics
	{
		Buffer::Buffer(const GLvoid* data, GLsizei size, GLenum usage)
		{
			glGenBuffers(1, &m_buffer_id);
			bind();
			glBufferData(GL_ARRAY_BUFFER, size, data, usage);
			unbind();
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &m_buffer_id);
		}

		void Buffer::bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
		}

		void Buffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void* Buffer::map(GLenum access) const
		{
			bind();
			return glMapBuffer(GL_ARRAY_BUFFER, access);
		}

		void Buffer::unmap() const
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			unbind();
		}
	}
}
