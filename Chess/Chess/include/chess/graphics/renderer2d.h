#pragma once
#include "renderable2d.h"

namespace Chess
{
	namespace Graphics
	{
		class Renderer2D
		{
		public:
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void flush() = 0;
		};
	}
}
