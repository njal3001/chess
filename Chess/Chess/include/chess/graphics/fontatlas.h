#include <string>
#include <unordered_map>
#include "chess/maths/maths.h"
#include "chess/graphics/texture.h"
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
            const unsigned int m_atlas_heigth;
            FT_Face m_face;
            std::unordered_map<char, Character> m_characters;
            Texture* m_texture;

        public:
            FontAtlas(const std::string& font_path, unsigned int font_size, unsigned int atlas_height);
            ~FontAtlas();

            bool init();

        };
    }
}
