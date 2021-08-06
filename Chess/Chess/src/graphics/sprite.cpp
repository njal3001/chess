#include "chess/graphics/sprite.h"
#include "chess/graphics/renderer2d.h"

namespace Chess
{
	namespace Graphics
	{
		Sprite::Sprite(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color)
			: m_position(Maths::Vec3(position.x, position.y, 0)), m_size(size), m_color(color)
		{}

		void Sprite::submit(Renderer2D* renderer) const
		{
			renderer->submit(this, m_position, m_size, m_color);
		}

		const Maths::Vec3& Sprite::get_position() const
		{
			return m_position;
		}

		const Maths::Vec2& Sprite::get_size() const
		{
			return m_size;
		}

		const Maths::Vec4& Sprite::get_color() const
		{
			return m_color;
		}

	}
}