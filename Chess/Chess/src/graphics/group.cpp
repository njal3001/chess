#include "chess/graphics/group.h"
#include "chess/graphics/batchrenderer2d.h"

namespace Game
{
	Group::Group(const Mat4x4& transformation_matrix)
		: m_transformation_matrix(transformation_matrix)
	{}

	Group::~Group()
	{
		for (unsigned int i = 0; i < m_renderables.size(); i++)
			delete m_renderables[i];
	}

	void Group::add(Renderable2D* renderable)
	{
		m_renderables.push_back(renderable);
	}

	void Group::submit(BatchRenderer2D* renderer) const
	{
		if (hidden) return;

		renderer->push_transformation(m_transformation_matrix);

		for (const Renderable2D* renderable : m_renderables)
			renderable->submit(renderer);

		renderer->pop_transformation();
	}
	
	void Group::transform(const Mat4x4& transform_matrix)
	{
		m_transformation_matrix *= transform_matrix;
	}

	const Mat4x4& Group::get_transformation_matrix() const
	{
		return m_transformation_matrix;
	}
}