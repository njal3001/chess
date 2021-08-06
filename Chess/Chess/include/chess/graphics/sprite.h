#pragma once
#include "renderable2d.h"

namespace Chess
{
	namespace Graphics
	{
		class Sprite : public Renderable2D
		{
		protected:
			Maths::Vec3 m_position;
			Maths::Vec2 m_size;
			Maths::Vec4 m_color;

		public:
			Sprite(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color);

			void submit(Renderer2D* renderer) const override;

			const Maths::Vec3& get_position() const;
			const Maths::Vec2& get_size() const;
			const Maths::Vec4& get_color() const;
		};
	}
}