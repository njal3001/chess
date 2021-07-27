#pragma once
#include <GL/glew.h>

namespace Chess
{
	namespace Graphics
	{
		class Buffer
		{
		private:
			GLuint m_buffer_id;
			GLuint m_component_count;
		
		public:
			Buffer(GLfloat* data, GLsizei count, GLuint component_count);

			void bind() const;
			void unbind() const;

			GLuint get_component_count() const;
		};
	}
}
