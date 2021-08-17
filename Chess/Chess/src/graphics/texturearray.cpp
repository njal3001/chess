#include "chess/graphics/texturearray.h"
#include "chess/utils/imageload.h"

namespace Chess
{
    namespace Graphics
    {
        TextureArray::TextureArray(const unsigned int max_layers, const Maths::Vec2& max_size)
        {
            glGenTextures(1, &m_id);
            bind();
            glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, max_size.x, max_size.y, max_layers,
                    0, GL_BGR, GL_UNSIGNED_BYTE, nullptr);
           unbind(); 
        }

        TextureArray::~TextureArray()
        {
            glDeleteTextures(1, &m_id);
        }

        const TextureArray::Element TextureArray::add(const std::string& filename)
        {
            return { this, 0, Maths::Vec2(0, 0) };
        }

        void TextureArray::bind() const
        {
            glBindTexture(GL_TEXTURE_2D_ARRAY, m_id);
        }

        void TextureArray::unbind() const
        {
            glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        }

        const unsigned int TextureArray::get_layers() const
        {
            return m_layers;
        }
    }
}
