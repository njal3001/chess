#pragma once
#include "renderable2d.h"
#include "texturearray.h"
#include "fontatlas.h"
#include "chess/maths/maths.h"

namespace Game
{
    class Label : public Renderable2D
    {
    private:
        const FontAtlas* m_font_atlas;
        const TextureArray::Element m_texture;
        std::string m_text;
        Vec2 m_position;
        Vec2 m_size;
        Vec4 m_color;

    public:
        Label(const FontAtlas* font_atlas, const TextureArray::Element& texture, const std::string& text, const Vec2& position, const Vec2& size, const Vec4& color);

        void submit(BatchRenderer2D* renderer) const override;
    };
}
