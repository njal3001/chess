#include "chess/graphics/buffers/bufferlayout.h"

namespace Chess
{
    namespace Graphics
    {
        BufferLayout::BufferLayout()
            : m_stride(0)
        {}

        void BufferLayout::push(GLenum type, int count, GLboolean normalized)
        {
            unsigned int offset = 0;
            switch (type)
            {
            case GL_FLOAT: 
                offset = sizeof(GLfloat) * count;
                break;
            case GL_UNSIGNED_INT: 
                offset = sizeof(GLuint) * count; 
                break;
            case GL_UNSIGNED_BYTE: 
                offset = sizeof(GLubyte) * count; 
                break;
            default:
                std::cout << "Type not supported!" << std::endl;
                return;
            }

            m_elements.push_back({ count, type, normalized, offset });
            m_stride += offset;
        }

        const std::vector<LayoutElement>& BufferLayout::get_elements() const
        {
            return m_elements;
        }
        
        GLsizei BufferLayout::get_stride() const
        {
            return m_stride;
        }
    }
}
