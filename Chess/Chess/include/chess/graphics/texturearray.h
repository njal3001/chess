#pragma once
#include <GL/glew.h>
#include <string>
#include "chess/maths/maths.h"
#include <map>

namespace Game
{
    class TextureArray
    {
    public:
        const struct Element
        {
            GLuint array_id;
            unsigned int layer;
            Vec2 uv_scale;
        };

    private:
        GLuint m_id;
        unsigned int m_max_layers;
        unsigned int m_layers;
        Vec2 m_max_size;
        GLuint m_format;
        std::map<std::string, Element> m_textures;

    public:
        TextureArray(const unsigned int max_layers, const Vec2& max_size, GLuint internal_format, GLuint format, const GLuint alignment);
        ~TextureArray();

        const Element add(const std::string& filename);
        const Element add(const void* pixels, const int width, const int height);
        void bind() const;
        void unbind() const;
        
        const GLuint get_id() const;
        const unsigned int get_layers() const;
    };
}
