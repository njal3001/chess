#include "chess/graphics/uilayer.h"

namespace Chess
{
	namespace Graphics
	{
		UILayer::UILayer(Shader* shader, float left, float right, float bottom, float top, float near, float far)
			: Layer(new BatchRenderer2D(), shader, Maths::Mat4x4::create_orthographic(left, right, bottom, top, near, far))
		{}
	}
}
