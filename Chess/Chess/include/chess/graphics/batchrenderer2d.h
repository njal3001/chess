#pragma once
#include "buffers/vertexarray.h"
#include "buffers/indexbuffer.h"
#include "buffers/indexbuffer.h"
#include "renderable2d.h"
#include "texturearray.h"
#include "fontatlas.h"
#include <vector>

namespace Game
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

		std::vector<Mat4x4> m_transformation_stack;
		Mat4x4 m_transformation_back;

	public:
		BatchRenderer2D(GLuint texture_array_id);
		~BatchRenderer2D();
		void begin();
		void submit(const Vec3& position,
			const Vec2& size, const std::vector<Vec2>& uv, 
			const Vec4& color);
		void submit(const Vec3& position,
			const Vec2& size, const std::vector<Vec2>& uv, 
			const Vec4& color, const TextureArray::Element& texture);
		void end();
		void flush();

		void push_transformation(Mat4x4 matrix, bool absolute = false);
		Mat4x4 pop_transformation();
		Mat4x4 peek_transformation();


	private:
		void init();
		void submit(const Vec3& position, const Vec2& size,
				const std::vector<Vec2>& uv, const unsigned int color, const int texture_layer, const Vec2& uv_scale);
	};
}
