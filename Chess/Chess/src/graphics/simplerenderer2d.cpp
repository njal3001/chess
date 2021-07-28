#include "chess\graphics\simplerenderer2d.h"

namespace Chess
{
	namespace Graphics
	{
		void SimpleRenderer2D::submit(const Renderable2D* renderable)
		{
			m_render_queue.push_back(renderable);
		}

		void SimpleRenderer2D::flush()
		{
			while (!m_render_queue.empty())
			{
				const Renderable2D* renderable = m_render_queue.front();
				renderable->get_vao()->bind();
				renderable->get_ibo()->bind();
				
				renderable->get_shader().set_uniform_mat4("ml_matrix", Maths::Mat4x4::create_translation(renderable->get_position()));
				glDrawElements(GL_TRIANGLES, renderable->get_ibo()->get_count(), GL_UNSIGNED_SHORT, nullptr);

				renderable->get_ibo()->unbind();
				renderable->get_vao()->unbind();

				m_render_queue.pop_front();
			}
		}
	}
}