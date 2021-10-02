#pragma once
#include "renderable2d.h"

namespace Chess
{
	namespace Graphics
	{
		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> m_renderables;
			Maths::Mat4x4& m_transformation_matrix;

		public:
			Group(const Maths::Mat4x4& transformation_matrix);
			~Group();

			void add(Renderable2D* renderable);
			void submit(BatchRenderer2D* renderer) const override;

			Maths::Mat4x4& get_transformation_matrix() const;
		};
	}
}
