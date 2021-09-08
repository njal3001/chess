#include "chess/graphics/fontmanager.h"
#include <iostream>
#include <algorithm>

namespace Chess 
{
    namespace Graphics
    {
        FontManager::FontManager(const std::string& font_path, unsigned int font_height)
            : m_font_path(font_path), m_font_height(font_height), m_library(0), m_face(0)
        {}

        bool FontManager::init()
        {
            if (FT_Init_FreeType(&m_library))
            {
                std::cout << "Could not initialize FreeType library" << std::endl;
                return false;
            }

            if (FT_New_Face(m_library, m_font_path.c_str(), 0, &m_face))
            {
                std::cout << "Failed to load font: " << m_font_path << std::endl;
                return false;
            }

            FT_Set_Pixel_Sizes(m_face, 0, m_font_height);

            FT_GlyphSlot g = m_face->glyph;
            unsigned int w = 0;
            unsigned int h = 0;

            for (char c = 32; c < 128; c++)
            {
                if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
                {
                    std::cout << "Failed to load character: " << c << std::endl;
                    continue;
                }
                
                w += g->bitmap.width;
                h = std::max(h, g->bitmap.rows);

                Character character =
                {
                    Maths::Vec2(g->bitmap.width, g->bitmap.rows),
                    Maths::Vec2(g->bitmap_left, g->bitmap_top),
                    g->advance.x
                }
            }

            return true;
        }

        FontManager::~FontManager()
        {
            FT_Done_Face(m_face);
            FT_Done_FreeType(m_library);
        }
    }
}
