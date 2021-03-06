#pragma once
#include "chess/graphics/batchrenderer2d.h"
#include "chess/graphics/renderable2d.h"
#include "chess/maths/maths.h"
#include <vector>

namespace Game
{
	class Layer
	{
	private:
		BatchRenderer2D* m_renderer;
		std::vector<Renderable2D*> m_renderables;
		Shader* m_shader;
		Mat4x4 m_projection_matrix;
	
	public:
		Layer(GLuint texture_array_id, Shader* shader, const Mat4x4& projection_matrix);
		~Layer();

		BatchRenderer2D* get_renderer() const;
		void set_projection(const Mat4x4& projection_matrix);
		void add(Renderable2D* renderable);
		void render();
	};
}
