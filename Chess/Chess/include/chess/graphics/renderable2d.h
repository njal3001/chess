#pragma once
#include "chess/maths/maths.h"
#include "buffers/vertexarray.h"
#include "buffers/indexbuffer.h"
#include "shader.h"

namespace Chess
{
	namespace Graphics
	{
		struct VertexData
		{
			Maths::Vec3 position;
			Maths::Vec4 color;
		};

		class Renderable2D
		{
		protected:
			Maths::Vec3 m_position;
			Maths::Vec2 m_size;
			Maths::Vec4 m_color;

		public:
			Renderable2D(Maths::Vec3 position, Maths::Vec2 size, Maths::Vec4 color);
			virtual ~Renderable2D();

			const Maths::Vec3& get_position() const;
			const Maths::Vec2& get_size() const;
			const Maths::Vec4& get_color() const;
		};
	}
}