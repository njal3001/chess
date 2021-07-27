#include "chess\graphics\buffers\vertexarray.h"

namespace Chess
{
	namespace Graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_array_id);
		}

		VertexArray::~VertexArray()
		{
			for (int i = 0; i < m_buffers.size(); i++)
				delete m_buffers[i];
		}

		void VertexArray::add_buffer(Buffer* buffer, GLuint index)
		{
			bind();
			buffer->bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->get_component_count(), GL_FLOAT, GL_FALSE, 0, 0);

			buffer->unbind();
			unbind();
		}

		void VertexArray::bind() const
		{
			glBindVertexArray(m_array_id);
		}

		void VertexArray::unbind() const
		{
			glBindVertexArray(0);
		}
	}
}

