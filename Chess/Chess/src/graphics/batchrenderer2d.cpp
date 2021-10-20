#include "chess/graphics/batchrenderer2d.h"

namespace Game
{
	BatchRenderer2D::BatchRenderer2D(GLuint texture_array_id)
		: m_texture_array_id(texture_array_id)
	{
		m_transformation_stack.push_back(Mat4x4::identity);
		m_transformation_back = Mat4x4::identity;
		init();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete m_vbo;
		delete m_ibo;
		delete m_vao;
	}

	void BatchRenderer2D::init()
	{
		m_vao = new VertexArray();
		m_vbo = new Buffer((const GLvoid*)NULL, RENDERER_BUFFER_SIZE, GL_DYNAMIC_DRAW);

		BufferLayout layout;
		layout.push(GL_FLOAT, 3, GL_FALSE); // Position
		layout.push(GL_FLOAT, 2, GL_FALSE); // UV
		layout.push(GL_INT, 1, GL_FALSE); // Texture layer
		layout.push(GL_UNSIGNED_BYTE, 4, GL_TRUE); // Color

		m_vao->add_buffer(*m_vbo, layout);

		GLushort* indices = new GLushort[RENDERER_INDICES_SIZE];

		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			indices[i] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset;

			offset += 4;
		}

		m_ibo = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
	}

	void BatchRenderer2D::submit(const Vec3& position,
		const Vec2& size, const std::vector<Vec2>& uv, const Vec4& color)
	{
		TextureArray::Element texture =
		{
			(unsigned int)0, (unsigned int)-1
		};

		submit(position, size, uv, color, texture);   
	}

	void BatchRenderer2D::submit(const Vec3& position,
		const Vec2& size, const std::vector<Vec2>& uv, 
		const Vec4& color, const TextureArray::Element& texture)
	{
		int r = (int)(color.x * 255.0f);
		int g = (int)(color.y * 255.0f);
		int b = (int)(color.z * 255.0f);
		int a = (int)(color.w * 255.0f);

		unsigned int c = a << 24 | b << 16 | g << 8 | r;

		submit(position, size, uv, c, texture.layer, texture.uv_scale);   
	}

	void BatchRenderer2D::submit(const Vec3& position,
		const Vec2& size, const std::vector<Vec2>& uv, const unsigned int color, const int texture_layer, const Vec2& uv_scale)
	{
		VertexData vertex_data[4];
		VertexData* vp = vertex_data;

		vp->position = m_transformation_back * position;
		float z = vp->position.z;

		vp->uv = uv[0] * uv_scale;
		vp->texture_layer = texture_layer;
		vp->color = color;
		vp++;
		
		vp->position = m_transformation_back * Vec3(position.x, position.y + size.y, position.z);
		vp->uv = uv[1] * uv_scale;
		vp->texture_layer = texture_layer;
		vp->color = color;
		vp++;

		vp->position = m_transformation_back * Vec3(position.x + size.x, position.y + size.y, position.z);
		vp->uv = uv[2] * uv_scale;
		vp->texture_layer = texture_layer;
		vp->color = color;
		vp++;

		vp->position = m_transformation_back * Vec3(position.x + size.x, position.y, position.z);
		vp->uv = uv[3] * uv_scale;
		vp->texture_layer = texture_layer;
		vp->color = color;
		vp++;

		auto front = m_vertex_data.begin();

		while(front != m_vertex_data.end())
		{
			if (front->position.z > z)
			{
				for (int i = 0; i < 4; i++)
				{
					m_vertex_data.insert(front, vertex_data[i]);
					std::next(front);
				}

				return;
			}
			
			std::advance(front, 4);
		}

		for (int i = 0; i < 4; i++)
		{
			m_vertex_data.insert(m_vertex_data.end(), vertex_data[i]);
		}
	}

	void BatchRenderer2D::flush()
	{
		VertexData* buffer_map = (VertexData*)m_vbo->map(GL_WRITE_ONLY);

		for (VertexData vd : m_vertex_data)
		{
			buffer_map->position = vd.position;
			buffer_map->uv = vd.uv;
			buffer_map->texture_layer = vd.texture_layer;
			buffer_map->color = vd.color;
			buffer_map++;
		}

		m_vbo->unmap();

		int index_count = 6 * (m_vertex_data.size() / 4);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture_array_id);

		m_vao->bind();
		m_ibo->bind();

		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_SHORT, NULL);

		m_ibo->unbind();
		m_vao->unbind();

		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

		m_vertex_data.clear();
	}

	void BatchRenderer2D::push_transformation(Mat4x4 matrix, bool absolute)
	{
		m_transformation_stack.push_back(matrix);
		if (absolute)
			m_transformation_back = matrix;
		else
			m_transformation_back = m_transformation_back * matrix;
	}

	Mat4x4 BatchRenderer2D::pop_transformation()
	{
		Mat4x4 prev_matrix = m_transformation_back;
		if (m_transformation_stack.size() > 1) {
			m_transformation_stack.pop_back();
			m_transformation_back = m_transformation_stack.back();
		}
		return prev_matrix;
	}

	Mat4x4 BatchRenderer2D::peek_transformation()
	{
		return m_transformation_back;
	}
}