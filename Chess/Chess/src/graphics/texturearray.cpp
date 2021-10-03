#include "chess/graphics/texturearray.h"
#include "chess/graphics/image.h"
#include <iostream>

namespace Chess
{
    namespace Graphics
    {
        TextureArray::TextureArray(const unsigned int max_layers, const Maths::Vec2& max_size, GLuint internal_format, GLuint format, const GLuint alignment)
            : m_layers(0), m_max_size(max_size), m_format(format)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
            glGenTextures(1, &m_id);
            bind();

            glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, internal_format, (GLsizei)max_size.x, (GLsizei)max_size.y, max_layers,
                    0, format, GL_UNSIGNED_BYTE, nullptr);
            
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
            // TODO: Bit of a quick fix, should have a resource manager maybe
            if (m_textures.find(filename) != m_textures.end())
                return m_textures[filename];

            Image image(filename);
            const int width = image.get_width();
            const int height = image.get_height();
            unsigned int layers = m_layers;
            m_layers++;
            bind();
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layers, width,
                    height, 1, m_format, GL_UNSIGNED_BYTE, image.get_bits());
            unbind();

            const Maths::Vec2 uv_scale = Maths::Vec2(width / m_max_size.x, height / m_max_size.y);

            m_textures[filename] = { m_id, layers, uv_scale };

            return m_textures[filename];
        }

        const TextureArray::Element TextureArray::add(const void* pixels, const int width, const int height)
        {
            unsigned int layers = m_layers;
            m_layers++;
            bind();
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layers, width,
                    height, 1, m_format, GL_UNSIGNED_BYTE, pixels);
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
