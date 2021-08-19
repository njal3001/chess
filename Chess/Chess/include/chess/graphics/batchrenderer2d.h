#pragma once
#include "renderer2d.h"
#include <vector>

namespace Chess
{
	namespace Graphics
	{
#define RENDERER_MAX_SPRITES 10000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

#define SHADER_POSITION_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TID_INDEX 2
#define SHADER_COLOR_INDEX 3

		class BatchRenderer2D : public Renderer2D
		{
		private:
			VertexArray* m_vao;
			Buffer* m_vbo;
			IndexBuffer* m_ibo;
			GLsizei m_index_count;
			VertexData* m_buffer_map;
            GLuint m_texture_array_id;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();
			void begin() override;
			void submit(const Renderable2D* renderable, const Maths::Vec3& position,
				const Maths::Vec2& size, const std::vector<Maths::Vec2>& uv, const Maths::Vec4& color) override;
			void submit(const Renderable2D* renderable, const Maths::Vec3& position,
				const Maths::Vec2& size, const std::vector<Maths::Vec2>& uv, const TextureArray::Element& texture) override;
			void end() override;
			void flush() override;

		private:
			void init();
            void submit(const Renderable2D* renderable, const Maths::Vec3& position, const Maths::Vec2& size,
                    const std::vector<Maths::Vec2>& uv, const unsigned int color, const int texture_layer, const float uv_offset);
		};
	}
}
