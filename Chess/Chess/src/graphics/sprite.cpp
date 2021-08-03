#include "chess\graphics\sprite.h"

namespace Chess
{
	namespace Graphics
	{
		Sprite::Sprite(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color)
			: Renderable2D(Maths::Vec3(position.x, position.y, 0), size, color) {}
	}
}