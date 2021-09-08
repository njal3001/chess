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
            unsigned int advance;
        }

        class FontManager
        {
        private:
            FT_Library m_library;
            const std::string m_font_path;
            const unsigned int m_font_height;
            FT_Face m_face;
            std::unordered_map<char, Character> m_characters;

        public:
            FontManager(const std::string& font_path, unsigned int font_size);
            ~FontManager();

            bool init();

        };
    }
}
