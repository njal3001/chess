#pragma once
#include "buffers/vertexarray.h"
#include "buffers/indexbuffer.h"
#include "buffers/indexbuffer.h"
#include "renderable2d.h"
#include "texturearray.h"
#include "fontatlas.h"
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

		class BatchRenderer2D
		{
		private:
			VertexArray* m_vao;
			Buffer* m_vbo;
			IndexBuffer* m_ibo;
			GLsizei m_index_count;
			VertexData* m_buffer_map;
            GLuint m_texture_array_id;

			std::vector<Maths::Mat4x4> m_transformation_stack;
			Maths::Mat4x4 m_transformation_back;

		public:
			BatchRenderer2D(GLuint texture_array_id);
			~BatchRenderer2D();
			void begin();
			void submit(const Maths::Vec3& position,
				const Maths::Vec2& size, const std::vector<Maths::Vec2>& uv, 
                const Maths::Vec4& color);
			void submit(const Maths::Vec3& position,
				const Maths::Vec2& size, const std::vector<Maths::Vec2>& uv, 
                const Maths::Vec4& color, const TextureArray::Element& texture);
			void end();
			void flush();

			void push_transformation(Maths::Mat4x4 matrix, bool absolute = false);
			Maths::Mat4x4 pop_transformation();
			Maths::Mat4x4 peek_transformation();


		private:
			void init();
            void submit(const Maths::Vec3& position, const Maths::Vec2& size,
                    const std::vector<Maths::Vec2>& uv, const unsigned int color, const int texture_layer, const Maths::Vec2& uv_scale);
		};
	}
}
