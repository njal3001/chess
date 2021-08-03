#include <iostream> 
#include "chess/graphics/window.h"
#include "chess/utils/file.h"
#include "chess/graphics/shader.h"
#include "chess/maths/maths.h"
#include "chess/graphics/buffers/buffer.h"
#include "chess/graphics/buffers/vertexarray.h"
#include "chess/graphics/buffers/indexbuffer.h"
#include "chess/graphics/renderable2d.h"
#include "chess/graphics/simplerenderer2d.h"
#include "chess/graphics/batchrenderer2d.h"
#include "chess/graphics/sprite.h"

int main()
{
	using namespace Chess;
	using namespace Graphics;
	using namespace Maths;

	Window window("Chess", 960, 540);
	glClearColor(0, 0, 0, 1);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();

	Mat4x4 ortho = Mat4x4::create_orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	shader.set_uniform_mat4("pr_matrix", ortho);

	std::vector<Renderable2D*> sprites;

	srand(time(NULL));


	BatchRenderer2D renderer;

	Sprite sprite(Vec2(0, 0), Vec2(0.5f, 0.5f), Vec4(1, 0, 1, 1));

	for (float y = 0; y < 9.0f; y += 0.13f)
	{
		for (float x = 0; x < 16.0f; x += 0.13f)
		{
			sprites.push_back(new Sprite(Maths::Vec2(x, y), Maths::Vec2(0.08f, 0.08f), Maths::Vec4((float)rand() / RAND_MAX, 0, 1, 1)));
		}
	}

	while (!window.closed())
	{
		window.clear();

		Vec2 mouse_pos = window.get_mouse_pos();
		Vec2 light_pos = Vec2(mouse_pos.x * (16.0f / 960.0f), 9.0f - mouse_pos.y * (9.0f / 540.0f));
		shader.set_uniform_2f("light_pos", light_pos);

		renderer.begin();
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
		renderer.end();
		renderer.flush();

		std::cout << "Sprites: " << sprites.size() << std::endl;
		window.update();
	}
}