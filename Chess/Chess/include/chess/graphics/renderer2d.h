#pragma once
#include "renderable2d.h"

namespace Chess
{
	namespace Graphics
	{
		class Renderer2D
		{
		protected:
			std::vector<Maths::Mat4x4> m_transformation_stack;
			Maths::Mat4x4 m_transformation_back;

		protected:
			Renderer2D();

		public:
			virtual void begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void end() {}
			virtual void flush() = 0;
			void push_transformation(Maths::Mat4x4 matrix, bool absolute = false);
			Maths::Mat4x4 pop_transformation();
			Maths::Mat4x4 peek_transformation();
		};
	}
}
