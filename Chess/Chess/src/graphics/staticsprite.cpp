#include "chess/graphics/staticsprite.h"

namespace Chess
{
	namespace Graphics
	{
		StaticSprite::StaticSprite(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color, Shader& shader)
		: Renderable2D(Maths::Vec3(position.x, position.y, 0), size, color), m_shader(shader) 
		{
			m_vertex_array = new VertexArray();
			GLfloat positions[] = 
			{
				0, 0, 0,
				0, m_size.y, 0,
				m_size.x, m_size.y, 0,
				m_size.x, 0, 0
			};

			GLfloat colors[] =
			{
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			m_vertex_array->add_buffer(new Buffer(positions, 4 * 3, 3), 0);
			m_vertex_array->add_buffer(new Buffer(colors, 4 * 4, 4), 1);

			GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
			m_index_buffer = new IndexBuffer(indices, 6);
		}

		StaticSprite::~StaticSprite()
		{
			delete m_vertex_array;
			delete m_index_buffer;
		}

		const VertexArray* StaticSprite::get_vao() const
		{
			return m_vertex_array;
		}

		const IndexBuffer* StaticSprite::get_ibo() const
		{
			return m_index_buffer;
		}

		Shader& StaticSprite::get_shader() const
		{
			return m_shader;
		}
	}
}