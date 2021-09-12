#pragma once
#include <FreeImage.h>
#include <string>
#include <GL/glew.h>
#include "chess/maths/maths.h"

namespace Chess
{
    namespace Graphics
    {
        class Texture
        {
        private:
            std::string m_filename;
            GLuint m_texture_id;
            GLsizei m_width, m_height;

        public:
            Texture(const std::string& filename, GLuint internal_format, GLuint format);
            Texture(const Maths::Vec2& size, const void* pixels, GLuint internal_format, GLuint format);
            ~Texture();

            void bind() const;
            void unbind() const;

            const GLuint get_id() const;
            const GLsizei get_width() const;
            const GLsizei get_height() const;

        private:
            GLuint load(const void* pixels, GLuint internal_format, GLuint format);
        };
    }
}
