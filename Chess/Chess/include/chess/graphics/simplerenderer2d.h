#pragma once
#include <deque>
#include "renderer2d.h"
#include "staticsprite.h"

namespace Chess
{
	namespace Graphics
	{
		class SimpleRenderer2D : public Renderer2D
		{
		private:
			// TODO: Can only use static sprite for now 
			std::deque<const StaticSprite*> m_render_queue;

		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;
		};
	}
}
