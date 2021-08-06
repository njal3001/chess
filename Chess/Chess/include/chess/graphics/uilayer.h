#pragma once
#include "layer.h"
#include "batchrenderer2d.h"

namespace Chess
{
	namespace Graphics
	{
		class UILayer : public Layer
		{
		public:
			UILayer(Shader* shader, float left, float right, float bottom, float top, float near, float far);
		};
	}
}
