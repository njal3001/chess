#pragma once
#include "chess/maths/maths.h"
#include "buffers/vertexarray.h"
#include "buffers/indexbuffer.h"
#include "shader.h"


namespace Chess
{
	namespace Graphics
	{
		class Renderer2D;

		struct VertexData
		{
			Maths::Vec3 position;
            Maths::Vec2 uv;
            float texture_slot;
			unsigned int color;
		};
	
		class Renderable2D
		{
		public:
			virtual ~Renderable2D() {};

			virtual void submit(Renderer2D* renderer) const = 0;
		};
	}
}
