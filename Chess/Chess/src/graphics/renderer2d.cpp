#include "chess/graphics/renderer2d.h"

namespace Chess
{
	namespace Graphics
	{
		Renderer2D::Renderer2D()
		{
			m_transformation_stack.push_back(Maths::Mat4x4::identity);
			m_transformation_back = Maths::Mat4x4::identity;
		}

		void Renderer2D::push_transformation(Maths::Mat4x4 matrix, bool absolute)
		{
			m_transformation_stack.push_back(matrix);
			if (absolute)
				m_transformation_back = matrix;
			else
				m_transformation_back = m_transformation_back * matrix;
		}

		Maths::Mat4x4 Renderer2D::pop_transformation()
		{
			Maths::Mat4x4 prev_matrix = m_transformation_back;
			if (m_transformation_stack.size() > 1) {
				m_transformation_stack.pop_back();
				m_transformation_back = m_transformation_stack.back();
			}
			return prev_matrix;
		}

		Maths::Mat4x4 Renderer2D::peek_transformation()
		{
			return m_transformation_back;
		}
	}
}