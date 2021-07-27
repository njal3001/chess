#pragma once
#include <GL/glew.h>

namespace Chess
{
	namespace Graphics
	{
		class IndexBuffer
		{
		private:
			GLuint m_buffer_id;
			GLuint m_count;

		public:
			IndexBuffer(GLushort* data, GLsizei count);

			void bind() const;
			void unbind() const;

			GLuint get_count() const;
		};
	}
}