#pragma once
#include "renderable2d.h"

namespace Chess
{
	namespace Graphics
	{
		class StaticSprite : public Renderable2D
		{
		private: 
			VertexArray* m_vertex_array;
			IndexBuffer* m_index_buffer;
			Shader& m_shader;

		public:
			StaticSprite(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color, Shader& shader);
			~StaticSprite();

			const VertexArray* get_vao() const;
			const IndexBuffer* get_ibo() const;
			
			Shader& get_shader() const;
		};
	}
}
