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
			glDeleteVertexArrays(1, &m_array_id);
		}

		void VertexArray::add_buffer(const Buffer& buffer, const BufferLayout& layout)
		{
			bind();
			buffer.bind();

            const auto& elements = layout.get_elements();
            for (unsigned i = 0; i < elements.size(); i++)
            {
                const auto& element = elements[i];
                glEnableVertexAttribArray(i);

				// TODO: Hardcoded for now
				if (element.type == GL_INT)
					glVertexAttribIPointer(i, element.count, element.type, layout.get_stride(), (const void*)element.offset);
				else
					glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void*)element.offset);
            } 

			buffer.unbind();
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

