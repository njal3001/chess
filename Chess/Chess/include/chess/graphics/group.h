#pragma once
#include "renderable2d.h"

namespace Game
{
	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> m_renderables;
		Mat4x4 m_transformation_matrix;

	public:
		Group(const Mat4x4& transformation_matrix);
		~Group();

		void add(Renderable2D* renderable);
		void submit(BatchRenderer2D* renderer) const override;

		void transform(const Mat4x4& transform_matrix);
		const Mat4x4& get_transformation_matrix() const;
	};
}
