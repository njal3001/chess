#pragma once
#include <GL/glew.h>
#include <vector>
#include "buffer.h"

namespace Chess
{
	namespace Graphics
	{
		class VertexArray
		{
			GLuint m_array_id;
			std::vector<Buffer*> m_buffers;
		
		public:
			VertexArray();
			~VertexArray();

			void add_buffer(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;

		};
	}
}