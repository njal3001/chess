#pragma once
#include "renderable2d.h"

namespace Chess
{
	namespace Graphics
	{
		class Sprite : public Renderable2D
		{
		public:
			Sprite(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color);
		};
	}
}