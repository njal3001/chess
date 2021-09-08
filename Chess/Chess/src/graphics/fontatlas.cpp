#include "chess/graphics/fontatlas.h"
#include <iostream>
#include <algorithm>

namespace Chess 
{
    namespace Graphics
    {
        FontAtlas::FontAtlas(const std::string& font_path, unsigned int font_height, unsigned int atlas_height)
            : m_font_path(font_path), m_font_height(font_height), m_atlas_heigth(atlas_height), m_library(0), m_face(0), m_texture(nullptr)
        {}

        bool FontAtlas::init()
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

            for (int c = 32; c < 128; c++)
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
                    Maths::Vec2((float)g->bitmap.width, (float)g->bitmap.rows),
                    Maths::Vec2((float)g->bitmap_left, (float)g->bitmap_top),
                    (unsigned int)g->advance.x
                };

                m_characters[(char)c] = character;
            }

            return true;
        }

        FontAtlas::~FontAtlas()
        {
            FT_Done_Face(m_face);
            FT_Done_FreeType(m_library);
        }
    }
}
