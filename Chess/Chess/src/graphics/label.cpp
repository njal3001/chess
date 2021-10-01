#include "chess/graphics/label.h"
#include <vector>
#include <algorithm>
#include "chess/graphics/batchrenderer2d.h"

namespace Chess
{
    namespace Graphics
    {
        Label::Label(const FontAtlas* font_atlas, const TextureArray::Element& texture, const std::string& text,
                const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color)
            : m_font_atlas(font_atlas), m_texture(texture), m_text(text), m_position(position), m_size(size), m_color(color)
        {}

		void Label::submit(BatchRenderer2D* renderer) const
        {
            // TODO: Iterate over all characters and submit it to renderer

            unsigned int x = m_position.x;
            unsigned int y = m_position.y;

            for (int i = 0; i < m_text.length(); i++)
            {
                if (m_text[i] == '\n') 
                {
                    y -= (m_size.y + std::max((int)(m_size.y / 10), 1));
                    x = m_position.x;
                    continue;
                }

                Character c = m_font_atlas->get_character(m_text[i]);

                Maths::Vec3 c_pos = Maths::Vec3(x, y, 0.0f);

                std::vector<Maths::Vec2> uv;

                uv.push_back(c.uv0);
                uv.push_back(Maths::Vec2(c.uv0.x, c.uv1.y));
                uv.push_back(c.uv1);
                uv.push_back(Maths::Vec2(c.uv1.x, c.uv0.y));

                renderer->submit(c_pos, m_size, uv, m_color, m_texture);

                x += m_size.x + std::max((int)(m_size.x / 10), 1);
            }
        }
    }
}
