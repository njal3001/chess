#pragma once
#include "renderable2d.h"
#include "texturearray.h"
#include <vector>

namespace Game
{
	class Sprite : public Renderable2D
	{
	protected:
		std::vector<Vec2> m_uv;
		TextureArray::Element m_texture;

	public:
		Vec3 position;
		Vec2 size;
		Vec4 color;

		Sprite(const Vec2& position, const Vec2& size, const Vec4& color);
		Sprite(const Vec2& position, const Vec2& size, const TextureArray::Element& texture);
		Sprite(const Vec2& position, const Vec2& size, const Vec4& color, const TextureArray::Element& texture);

		void submit(BatchRenderer2D* renderer) const override;

		const std::vector<Vec2>& get_uv() const;

	private:
		void set_uv_defaults();
	};
}
