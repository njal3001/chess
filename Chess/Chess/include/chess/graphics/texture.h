#pragma once
#include <FreeImage.h>
#include <string>
#include <GL/glew.h>

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
            Texture(const std::string& filename);
            ~Texture();

            void bind() const;
            void unbind() const;

            const GLuint get_id() const;
            const GLsizei get_width() const;
            const GLsizei get_height() const;

        private:
            GLuint load();
        };
    }
}
