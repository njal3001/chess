#include "chess\graphics\layer.h"

namespace Chess
{
	namespace Graphics
	{
		Layer::Layer(GLuint texture_array_id, Shader* shader, Maths::Mat4x4 projection_matrix)
			: m_renderer(new BatchRenderer2D(texture_array_id)), m_shader(shader), m_projection_matrix(projection_matrix)
		{
			shader->enable();
			shader->set_uniform_mat4("pr_matrix", projection_matrix);
			shader->disable();
		}

		Layer::~Layer()
		{
			delete m_renderer;
			for (unsigned int i = 0; i < m_renderables.size(); i++)
				delete m_renderables[i];
		}

		void Layer::add(Renderable2D* renderable)
		{
			m_renderables.push_back(renderable);
		}

		void Layer::render()
		{
			m_shader->enable();

			m_renderer->begin();
			for (const Renderable2D* renderable : m_renderables)
				renderable->submit(m_renderer);
			m_renderer->end();

			m_renderer->flush();

			m_shader->disable();
		}
	}
}
