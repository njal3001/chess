#include "chess/graphics/texturearray.h"
#include "chess/graphics/image.h"

namespace Chess
{
    namespace Graphics
    {
        TextureArray::TextureArray(const unsigned int max_layers, const Maths::Vec2& max_size)
            : m_layers(0), m_max_size(max_size)
        {
            glGenTextures(1, &m_id);
            bind();

            glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, max_size.x, max_size.y, max_layers,
                    0, GL_BGR, GL_UNSIGNED_BYTE, nullptr);
            
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            unbind(); 
        }

        TextureArray::~TextureArray()
        {
            glDeleteTextures(1, &m_id);
        }

        const TextureArray::Element TextureArray::add(const std::string& filename)
        {
            Image image(filename);
            const int width = image.get_width();
            const int height = image.get_height();
            unsigned int layers = m_layers;
            m_layers++;
            bind();
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layers, image.get_width(),
                    image.get_height(), 1, GL_BGR, GL_UNSIGNED_BYTE, image.get_bits());
            unbind();

            const Maths::Vec2 uv_scale = Maths::Vec2(width / m_max_size.x, height / m_max_size.y);

            return { m_id, layers, uv_scale };
        }

        void TextureArray::bind() const
        {
            glBindTexture(GL_TEXTURE_2D_ARRAY, m_id);
        }

        void TextureArray::unbind() const
        {
            glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        }

        const GLuint TextureArray::get_id() const
        {
            return m_id;
        }

        const unsigned int TextureArray::get_layers() const
        {
            return m_layers;
        }
    }
}
