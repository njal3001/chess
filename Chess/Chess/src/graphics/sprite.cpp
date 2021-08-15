#include "chess/graphics/sprite.h"
#include "chess/graphics/renderer2d.h"

namespace Chess
{
	namespace Graphics
	{
		Sprite::Sprite(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color)
			: m_position(Maths::Vec3(position.x, position.y, 0)), m_size(size), m_color(color), m_texture(nullptr)
		{
            set_uv_defaults(); 
        }


        Sprite::Sprite(const Maths::Vec2& position, const Maths::Vec2& size, Texture* texture)
			: Sprite(position, size, Maths::Vec4(1.0f, 1.0f, 1.0f, 1.0f)) 
        {
            m_texture = texture;
        }

        void Sprite::set_uv_defaults()
        {
            m_uv.push_back(Maths::Vec2(0, 0));            
            m_uv.push_back(Maths::Vec2(0, 1));            
            m_uv.push_back(Maths::Vec2(1, 1));            
            m_uv.push_back(Maths::Vec2(1, 0));            
        }

		void Sprite::submit(Renderer2D* renderer) const
		{
			renderer->submit(this, m_position, m_size, m_uv, m_color, get_texture_id());
		}

		const Maths::Vec3& Sprite::get_position() const
		{
			return m_position;
		}

		const Maths::Vec2& Sprite::get_size() const
		{
			return m_size;
		}

        const std::vector<Maths::Vec2>& Sprite::get_uv() const
        {
            return m_uv;
        }

        const GLuint Sprite::get_texture_id() const
        {
            return m_texture ? m_texture->get_id() : 0;
        }

		const Maths::Vec4& Sprite::get_color() const
		{
			return m_color;
		}
	}
}
