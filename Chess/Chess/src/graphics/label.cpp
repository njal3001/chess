#include "chess/graphics/label.h"
#include <vector>
#include <algorithm>
#include "chess/graphics/batchrenderer2d.h"

namespace Game
{
    Label::Label(const FontAtlas* font_atlas, const TextureArray::Element& texture, const std::string& text,
            const Vec3& position, const Vec2& size, const Vec4& color)
        : m_font_atlas(font_atlas), m_texture(texture), text(text), position(position), size(size), color(color)
    {}

    void Label::submit(BatchRenderer2D* renderer) const
    {
        if (hidden) return;

        unsigned int x = position.x;
        unsigned int y = position.y;

        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] == '\n') 
            {
                y -= (size.y + std::max((int)(size.y / 10), 1));
                x = position.x;
                continue;
            }

            if (text[i] == ' ') 
            {
                x += size.x;
                continue;
            }

            Character c = m_font_atlas->get_character(text[i]);

            Vec3 c_pos = Vec3(x, y, position.z);

            std::vector<Vec2> uv;

            uv.push_back(c.uv0);
            uv.push_back(Vec2(c.uv0.x, c.uv1.y));
            uv.push_back(c.uv1);
            uv.push_back(Vec2(c.uv1.x, c.uv0.y));

            renderer->submit(c_pos, size, uv, color, m_texture);

            x += size.x + std::max((int)(size.x / 10), 1);
        }
    }
}
