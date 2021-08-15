#pragma once
#include "renderable2d.h"
#include "texture.h"
#include <vector>

namespace Chess
{
	namespace Graphics
	{
		class Sprite : public Renderable2D
		{
		protected:
			Maths::Vec3 m_position;
			Maths::Vec2 m_size;
            std::vector<Maths::Vec2> m_uv;
            Texture* m_texture;
			Maths::Vec4 m_color;

		public:
			Sprite(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color);
			Sprite(const Maths::Vec2& position, const Maths::Vec2& size, Texture* texture);

			void submit(Renderer2D* renderer) const override;

			const Maths::Vec3& get_position() const;
			const Maths::Vec2& get_size() const;
            const std::vector<Maths::Vec2>& get_uv() const;
            const GLuint get_texture_id() const;
			const Maths::Vec4& get_color() const;

        private:
            void set_uv_defaults();
		};
	}
}
