#pragma once
#include "chess/maths/maths.h"
#include "buffers/vertexarray.h"
#include "buffers/indexbuffer.h"
#include "shader.h"


namespace Chess
{
	namespace Graphics
	{
		class BatchRenderer2D;

		struct VertexData
		{
			Maths::Vec3 position;
            Maths::Vec2 uv;
            int texture_layer;
			unsigned int color;
		};
	
		class Renderable2D
		{
		public:
			virtual ~Renderable2D() {};

			virtual void submit(BatchRenderer2D* renderer) const = 0;
		};
	}
}
