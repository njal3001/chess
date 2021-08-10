#pragma once
#include "chess/graphics/texture.h"
#include <FreeImage.h>
#include <string>
#include <GL/glew.h>
#include "chess/utils/imageload.h"

namespace Chess
{
    namespace Graphics
    {
        Texture::Texture(const std::string& filename)
            : m_filename(filename)
        {
            m_texture_id = load();
        }

        Texture::~Texture()
        {
            glDeleteTextures(1, &m_texture_id);
        }

        GLuint Texture::load()
        {
            BYTE* pixels = Utils::load_image(m_filename.c_str(), &m_width, &m_height);

            GLuint result;
            glGenTextures(1, &result);
            glBindTexture(GL_TEXTURE_2D, result);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
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
