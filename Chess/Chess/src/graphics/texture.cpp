#include "chess/graphics/texture.h"
#include <FreeImage.h>
#include "chess/graphics/image.h"

namespace Chess
{
    namespace Graphics
    {
        Texture::Texture(const std::string& filename)
            : m_filename(filename)
        {
            Image image(m_filename);
            m_width = image.get_width();
            m_height = image.get_height();
            m_texture_id = load(image.get_bits());
        }

        Texture::Texture(const Maths::Vec2& size, const void* pixels)
            : m_filename(""), m_width((GLsizei)size.x), m_height((GLsizei)size.y)
        {
            m_texture_id = load(pixels);
        }

        Texture::~Texture()
        {
            glDeleteTextures(1, &m_texture_id);
        }

        GLuint Texture::load(const void* pixels)
        {
            GLuint result;
            glGenTextures(1, &result);
            glBindTexture(GL_TEXTURE_2D, result);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR,
                GL_UNSIGNED_BYTE, pixels);

            glBindTexture(GL_TEXTURE_2D, 0);

            return result;
        }
        
        void Texture::bind() const
        {
            glBindTexture(GL_TEXTURE_2D, m_texture_id);
        }
        
        void Texture::unbind() const
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        } 

        const GLuint Texture::get_id() const
        {
            return m_texture_id;
        }

        const GLsizei Texture::get_width() const
        {
            return m_width;
        }

        const GLsizei Texture::get_height() const
        {
            return m_height;
        }
    }
}
