#pragma once
#include "chess/maths/maths.h"
#include "buffers/vertexarray.h"
#include "buffers/indexbuffer.h"
#include "shader.h"

namespace Chess
{
	namespace Graphics
	{
		class Renderable2D
		{
		protected:
			Maths::Vec3 m_position;
			Maths::Vec2 m_size;
			Maths::Vec4 m_color;

			VertexArray* m_vertex_array;
			IndexBuffer* m_index_buffer;
			Shader& m_shader;

		public:
			Renderable2D(Maths::Vec3 position, Maths::Vec2 size, Maths::Vec4 color, Shader& shader);
			virtual ~Renderable2D();

			const VertexArray* get_vao() const;
			const IndexBuffer* get_ibo() const;

			Shader& get_shader() const;

			const Maths::Vec3& get_position() const;
			const Maths::Vec2& get_size() const;
			const Maths::Vec4& get_color() const;
		};
	}
}