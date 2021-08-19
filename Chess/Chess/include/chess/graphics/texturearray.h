#pragma once
#include <GL/glew.h>
#include <string>
#include "chess/maths/maths.h"

namespace Chess
{
    namespace Graphics
    {
        class TextureArray
        {
        public:
            const struct Element
            {
                GLuint array_id;
                unsigned int layer;
                Maths::Vec2 uv_scale;
            };

        private:
            GLuint m_id;
            unsigned int m_max_layers;
            unsigned int m_layers;
            Maths::Vec2 m_max_size;

        public:
            TextureArray(const unsigned int max_layers, const Maths::Vec2& max_size);
            ~TextureArray();

            const Element add(const std::string& filename);
            void bind() const;
            void unbind() const;
            
            const GLuint get_id() const;
            const unsigned int get_layers() const;
        };
    }
}
