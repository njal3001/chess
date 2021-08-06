#include "chess\graphics\layer.h"

namespace Chess
{
	namespace Graphics
	{
		Layer::Layer(Renderer2D* renderer, Shader* shader, Maths::Mat4x4 projection_matrix)
			: m_renderer(renderer), m_shader(shader), m_projection_matrix(projection_matrix)
		{
			shader->enable();
			shader->set_uniform_mat4("pr_matrix", projection_matrix);
			shader->disable();
		}

		Layer::~Layer()
		{
			delete m_shader;
			delete m_renderer;
			for (int i = 0; i < m_renderables.size(); i++)
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
				m_renderer->submit(renderable);
			m_renderer->end();

			m_renderer->flush();

			m_shader->disable();
		}
	}
}
