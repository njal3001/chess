#pragma once
#include <GL/glew.h>
#include <vector>
#include "buffer.h"
#include "bufferlayout.h"

namespace Game
{
	class VertexArray
	{
		GLuint m_array_id;
	
	public:
		VertexArray();
		~VertexArray();

		void add_buffer(const Buffer& buffer, const BufferLayout& layout);
		void bind() const;
		void unbind() const;
	};
}
