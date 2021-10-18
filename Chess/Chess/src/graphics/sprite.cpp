#include "chess/graphics/sprite.h"
#include "chess/graphics/batchrenderer2d.h"

namespace Game
{
    Sprite::Sprite(const Vec2& position, const Vec2& size, const Vec4& color)
        : Sprite(position, size, color, {0, 0}) 
    {}


    Sprite::Sprite(const Vec2& position, const Vec2& size, const TextureArray::Element& texture)
        : Sprite(position, size, Vec4(1.0f, 1.0f, 1.0f, 1.0f), texture) 
    {}


    Sprite::Sprite(const Vec2& position, const Vec2& size, const Vec4& color, const TextureArray::Element& texture)
        : position(Vec3(position.x, position.y, 0)), size(size), color(color), m_texture(texture), transform(Mat4x4::identity)
    {
        set_uv_defaults(); 
    }

    void Sprite::set_uv_defaults()
    {
        m_uv.push_back(Vec2(0, 0));            
        m_uv.push_back(Vec2(0, 1));		       
        m_uv.push_back(Vec2(1, 1));            
        m_uv.push_back(Vec2(1, 0));            
    }

    void Sprite::submit(BatchRenderer2D* renderer) const
    {
        if (hidden) return;

        renderer->push_transformation(transform);
        if (m_texture.array_id != 0)
            renderer->submit(position, size, m_uv, color, m_texture);
        else
            renderer->submit(position, size, m_uv, color);
        renderer->pop_transformation();
    }

    const std::vector<Vec2>& Sprite::get_uv() const
    {
        return m_uv;
    }
}
