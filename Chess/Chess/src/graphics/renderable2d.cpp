#include "chess\graphics\renderable2d.h"

namespace Chess
{
	namespace Graphics
	{
		Renderable2D::Renderable2D(Maths::Vec3 position, Maths::Vec2 size, Maths::Vec4 color)
			: m_position(position), m_size(size), m_color(color) {}

		Renderable2D::~Renderable2D() {}

		const Maths::Vec3& Renderable2D::get_position() const
		{
			return m_position;
		}

		const Maths::Vec2& Renderable2D::get_size() const
		{
			return m_size;
		}

		const Maths::Vec4& Renderable2D::get_color() const
		{
			return m_color;
		}
	}
}
