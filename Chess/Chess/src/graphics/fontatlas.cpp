#include "chess/graphics/fontatlas.h"
#include <iostream>
#include <algorithm>

namespace Chess 
{
    namespace Graphics
    {
        FontAtlas::FontAtlas(const std::string& font_path, unsigned int font_height, unsigned int atlas_height)
            : m_font_path(font_path), m_font_height(font_height), m_atlas_height(atlas_height), m_library(0), m_face(0), m_texture(nullptr)
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

            unsigned int tex_w = m_atlas_height;
            unsigned int tex_h = m_atlas_height;
            unsigned int p_font_height = (m_face->size->metrics.height >> 6) + 1;
            
            char* pixels = new char[tex_w * tex_h];
            unsigned int px = 0;
            unsigned int py = 0;

            for (int c = 32; c < 128; c++)
            {
                if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
                {
                    std::cout << "Failed to load character: " << c << std::endl;
                    continue;
                }

                FT_Bitmap* bmp = &g->bitmap;

                if (px + bmp->width >= tex_w)
                {
                    px = 0;
                    py += p_font_height;
                }
                
                for (unsigned int row = 0; row < bmp->rows; row++)
                {
                    for (unsigned int col = 0; col < bmp->width; col++)
                    {
                        int x = px + col;
                        int y = py + row;
                        pixels[y * tex_w + x] = bmp->buffer[row * bmp->pitch + col];
                    }
                }

                Character character =
                {
                    Maths::Vec2((float)g->bitmap.width, (float)g->bitmap.rows),
                    Maths::Vec2((float)g->bitmap_left, (float)g->bitmap_top),
                    (unsigned int)g->advance.x,
                    Maths::Vec2(px / (float)tex_w, py / (float)tex_h),
                    Maths::Vec2((px + bmp->width) / (float)tex_w, (py + bmp->rows) / (float)tex_h)
                };

                m_characters[(char)c] = character;
            }

            m_texture = new Texture(Maths::Vec2((float)tex_w, (float)tex_h), pixels);

            delete[] pixels;
            
            return true;
        }

        FontAtlas::~FontAtlas()
        {
            FT_Done_Face(m_face);
            FT_Done_FreeType(m_library);
        }
    }
}
