#pragma once
#include <GL/glew.h>

namespace Game
{
	class Buffer
	{
	private:
		GLuint m_buffer_id;
		GLuint m_component_count;
	
	public:
		Buffer(const GLvoid* data, GLsizei size, GLenum usage);
		~Buffer();

		void bind() const;
		void unbind() const;

		void* map(GLenum access) const;
		void unmap() const;
	};
}
