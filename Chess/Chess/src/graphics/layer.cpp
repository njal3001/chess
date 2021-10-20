#include "chess\graphics\layer.h"

namespace Game
{
	Layer::Layer(GLuint texture_array_id, Shader* shader, const Mat4x4& projection_matrix)
		: m_renderer(new BatchRenderer2D(texture_array_id)), m_shader(shader), m_projection_matrix(projection_matrix)
	{}

	Layer::~Layer()
	{
		delete m_renderer;
		for (unsigned int i = 0; i < m_renderables.size(); i++)
			delete m_renderables[i];
	}
	
	void Layer::set_projection(const Mat4x4& projection_matrix)
	{
		m_projection_matrix = projection_matrix;
	}

	void Layer::add(Renderable2D* renderable)
	{
		m_renderables.push_back(renderable);
	}

	// TODO: Z value ordering somehow
	void Layer::render()
	{
		m_shader->enable();
		m_shader->set_uniform_mat4("pr_matrix", m_projection_matrix);

		for (const Renderable2D* renderable : m_renderables)
				renderable->submit(m_renderer);

		m_renderer->flush();

		m_shader->disable();
	}
}