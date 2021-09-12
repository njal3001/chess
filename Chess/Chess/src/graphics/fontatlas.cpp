#include "chess/graphics/fontatlas.h"
#include <iostream>
#include <algorithm>

namespace Chess 
{
    namespace Graphics
    {
        FontAtlas::FontAtlas(const std::string& font_path, unsigned int font_height, const Maths::Vec2& size)
            : m_font_path(font_path), m_font_height(font_height), m_size(size), m_library(0), m_face(0), m_pixels(nullptr)
        {}

        // TODO: Maybe just make a utils function that creates a font atlas instead
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

            // TODO: Calculate dimensions needed to fit all characters, hardcoded for now

            unsigned int tex_w = (unsigned int)m_size.x;
            unsigned int tex_h = (unsigned int)m_size.y;
            
            m_pixels = new unsigned char[tex_w * tex_h];
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
                    py += m_font_height;
                }

                if (py + bmp->rows > tex_h)
                {
                    std::cout << "Font atlas size exceeded at character: " << c << std::endl;
                    break;
                }
                
                for (unsigned int row = 0; row < bmp->rows; row++)
                {
                    for (unsigned int col = 0; col < bmp->width; col++)
                    {
                        int x = px + col;
                        int y = py + row;

                        // TODO: Fix warning
                        m_pixels[y * tex_w + x] = bmp->buffer[row * bmp->pitch + col];
                    }
                }

                std::cout << "Character: " << (char)c << std::endl;
                std::cout << "UV0: " << Maths::Vec2(px / (float)tex_w, py / (float)tex_h) << std::endl;
                std::cout << "UV1: " << Maths::Vec2((px + bmp->width) / (float)tex_w, (py + bmp->rows) / (float)tex_h)
                    << std::endl;

                Character character =
                {
                    Maths::Vec2((float)g->bitmap.width, (float)g->bitmap.rows),
                    Maths::Vec2((float)g->bitmap_left, (float)g->bitmap_top),
                    (unsigned int)g->advance.x,
                    Maths::Vec2(px / (float)tex_w, 1 - py / (float)tex_h),
                    Maths::Vec2((px + bmp->width) / (float)tex_w, (py + bmp->rows) / (float)tex_h)
                };

                m_characters[(char)c] = character;

                px += bmp->width + 1;
            }


            return true;
        }

        FontAtlas::~FontAtlas()
        {
            delete m_pixels;
            FT_Done_Face(m_face);
            FT_Done_FreeType(m_library);
        }

        const Maths::Vec2& FontAtlas::get_size() const
        {
            return m_size;
        }

        unsigned char* FontAtlas::get_pixels() const
        {
            return m_pixels;
        }

        const Character& FontAtlas::get_character(const char c) const
        {
            return m_characters.at(c);
        }
    }
}
