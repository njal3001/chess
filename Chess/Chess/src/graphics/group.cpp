#include "chess/graphics/group.h"

namespace Chess
{
	namespace Graphics 
	{
		Group::Group(const Maths::Mat4x4& transformation_matrix)
			: m_transformation_matrix(transformation_matrix)
		{}

		Group::~Group()
		{
			for (int i = 0; i < m_renderables.size(); i++)
				delete m_renderables[i];
		}

		void Group::add(Renderable2D* renderable)
		{
			m_renderables.push_back(renderable);
		}

		void Group::submit(Renderer2D* renderer) const
		{
			renderer->push_transformation(m_transformation_matrix);

			for (const Renderable2D* renderable : m_renderables)
				renderable->submit(renderer);

			renderer->pop_transformation();
		}
	}
}