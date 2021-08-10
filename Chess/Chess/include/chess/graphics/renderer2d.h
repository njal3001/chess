#pragma once
#include "renderable2d.h"
#include <vector>

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
			virtual void submit(const Renderable2D* renderable, const Maths::Vec3& position,
				const Maths::Vec2& size, const std::vector<Maths::Vec2>& uv, const Maths::Vec4& color) = 0;
			virtual void end() {}
			virtual void flush() = 0;
			void push_transformation(Maths::Mat4x4 matrix, bool absolute = false);
			Maths::Mat4x4 pop_transformation();
			Maths::Mat4x4 peek_transformation();
		};
	}
}
