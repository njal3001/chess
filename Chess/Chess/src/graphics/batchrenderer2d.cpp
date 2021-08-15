#include "chess/graphics/batchrenderer2d.h"

namespace Chess
{
	namespace Graphics
	{
		BatchRenderer2D::BatchRenderer2D()
			: m_index_count(0)
		{
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
            layout.push(GL_FLOAT, 1, GL_FALSE); // Texture slot
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

		void BatchRenderer2D::begin()
		{
			m_buffer_map = (VertexData*)m_vbo->map(GL_WRITE_ONLY);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable, const Maths::Vec3& position,
			const Maths::Vec2& size, const std::vector<Maths::Vec2>& uv, const Maths::Vec4& color, const GLuint tid)
		{
            unsigned int c = 0;
            float texture_slot = 0.0f;

            if (tid > 0)
            {
                bool found = false;
                for (int i = 0; i < m_texture_slots.size(); i++)
                {
                    if (m_texture_slots[i] == tid)
                    {
                        texture_slot = (float)(i + 1);
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    if (m_texture_slots.size() >= 32)
                    {
                        end();
                        flush();
                        begin();
                    }

                    m_texture_slots.push_back(tid);
                    texture_slot = (float)m_texture_slots.size();
                }
            } 
            else
            {
                int r = color.x * 255.0f;
                int g = color.y * 255.0f;
                int b = color.z * 255.0f;
                int a = color.w * 255.0f;

                c = a << 24 | b << 16 | g << 8 | r;
            }

			m_buffer_map->position = m_transformation_back * position;
			m_buffer_map->uv = uv[0];
            m_buffer_map->texture_slot = texture_slot;
			m_buffer_map->color = c;
			m_buffer_map++;
			
			m_buffer_map->position = m_transformation_back * Maths::Vec3(position.x, position.y + size.y, position.z);
			m_buffer_map->uv = uv[1];
            m_buffer_map->texture_slot = texture_slot;
			m_buffer_map->color = c;
			m_buffer_map++;

			m_buffer_map->position = m_transformation_back * Maths::Vec3(position.x + size.x, position.y + size.y, position.z);
			m_buffer_map->uv = uv[2];
            m_buffer_map->texture_slot = texture_slot;
			m_buffer_map->color = c;
			m_buffer_map++;

			m_buffer_map->position = m_transformation_back * Maths::Vec3(position.x + size.x, position.y, position.z);
			m_buffer_map->uv = uv[3];
            m_buffer_map->texture_slot = texture_slot;
			m_buffer_map->color = c;
			m_buffer_map++;

			m_index_count += 6;
		}

		void BatchRenderer2D::end()
		{
			m_vbo->unmap();
		}

		void BatchRenderer2D::flush()
		{
            for (int i = 0; i < m_texture_slots.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, m_texture_slots[i]);
            }

			m_vao->bind();
			m_ibo->bind();

			glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_SHORT, NULL);

			m_ibo->unbind();
			m_vao->unbind();

			m_index_count = 0;
		}
	}
}
