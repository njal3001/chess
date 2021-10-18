#pragma once
#include "chess/maths/maths.h"
#include "buffers/vertexarray.h"
#include "buffers/indexbuffer.h"
#include "shader.h"


namespace Game
{
	class BatchRenderer2D;

	struct VertexData
	{
		Vec3 position;
		Vec2 uv;
		int texture_layer;
		unsigned int color;
	};

	class Renderable2D
	{
	public:
		bool hidden;

		Renderable2D()
			: hidden(false) {};

		virtual ~Renderable2D() {};

		virtual void submit(BatchRenderer2D* renderer) const = 0;

	};
}
