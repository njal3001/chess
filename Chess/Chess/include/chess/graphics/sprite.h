#pragma once
#include "renderable2d.h"
#include "texturearray.h"
#include <vector>

namespace Chess
{
	namespace Graphics
	{
		class Sprite : public Renderable2D
		{
		protected:
            std::vector<Maths::Vec2> m_uv;
            TextureArray::Element m_texture;

		public:
			Maths::Vec3 position;
			Maths::Vec2 size;
			Maths::Vec4 color;

			Sprite(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color);
			Sprite(const Maths::Vec2& position, const Maths::Vec2& size, const TextureArray::Element& texture);
			Sprite(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color, const TextureArray::Element& texture);

			void submit(BatchRenderer2D* renderer) const override;

            const std::vector<Maths::Vec2>& get_uv() const;

        private:
            void set_uv_defaults();
		};
	}
}
