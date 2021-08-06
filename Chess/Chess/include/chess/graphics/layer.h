#pragma once
#include "chess/graphics/renderer2d.h"
#include "chess/graphics/renderable2d.h"
#include "chess/maths/maths.h"
#include <vector>

namespace Chess
{
	namespace Graphics
	{
		class Layer
		{
		protected:
			Renderer2D* m_renderer;
			std::vector<Renderable2D*> m_renderables;
			Shader* m_shader;
			Maths::Mat4x4 m_projection_matrix;
		
		protected:
			Layer(Renderer2D* renderer, Shader* shader, Maths::Mat4x4 projection_matrix);

		public:
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();
		};
	}
}
