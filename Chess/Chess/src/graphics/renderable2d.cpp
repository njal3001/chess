#include "chess\graphics\renderable2d.h"

namespace Chess
{
	namespace Graphics
	{
		Renderable2D::Renderable2D(Maths::Vec3 position, Maths::Vec2 size, Maths::Vec4 color, Shader& shader)
			: m_position(position), m_size(size), m_color(color), m_shader(shader)
		{
			m_vertex_array = new VertexArray();

			GLfloat vertices[] =
			{
				0, 0, 0,
				0, size.y, 0,
				size.x, size.y, 0,
				size.x, 0, 0
			};

			GLfloat colors[] =
			{
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			m_vertex_array->add_buffer(new Buffer(vertices, 4 * 3, 3), 0);
			m_vertex_array->add_buffer(new Buffer(colors, 4 * 4, 4), 1);

			GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
			m_index_buffer = new IndexBuffer(indices, 6);
		}

		Renderable2D::~Renderable2D()
		{
			delete m_vertex_array;
			delete m_index_buffer;
		}

		const VertexArray* Renderable2D::get_vao() const
		{
			return m_vertex_array;
		}

		const IndexBuffer* Renderable2D::get_ibo() const
		{
			return m_index_buffer;
		}

		Shader& Renderable2D::get_shader() const
		{
			return m_shader;
		}

		const Maths::Vec3& Renderable2D::get_position() const
		{
			return m_position;
		}

		const Maths::Vec2& Renderable2D::get_size() const
		{
			return m_size;
		}

		const Maths::Vec4& Renderable2D::get_color() const
		{
			return m_color;
		}
	}
}
