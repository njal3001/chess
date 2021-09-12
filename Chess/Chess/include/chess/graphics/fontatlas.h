#pragma once
#include <string>
#include <unordered_map>
#include "chess/maths/maths.h"
// Might cause errors
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Chess 
{
    namespace Graphics
    {
        struct Character
        {
            Maths::Vec2 size;
            Maths::Vec2 bearing;
            unsigned int advance = 0;
            Maths::Vec2 uv0;
            Maths::Vec2 uv1;
        };

        class FontAtlas
        {
        private:
            FT_Library m_library;
            const std::string m_font_path;
            const unsigned int m_font_height;
            const Maths::Vec2 m_size;
            FT_Face m_face;
            std::unordered_map<char, Character> m_characters;
            unsigned char* m_pixels;

        public:
            FontAtlas(const std::string& font_path, unsigned int font_size, const Maths::Vec2& size);
            ~FontAtlas();

            bool init();
            const Maths::Vec2& get_size() const;
            unsigned char* get_pixels() const;
            const Character& get_character(const char c) const;
        };
    }
}
