#include <iostream> 
#include "chess/graphics/window.h"
#include "chess/utils/file.h"
#include "chess/graphics/shader.h"
#include "chess/maths/maths.h"
#include "chess/graphics/buffers/buffer.h"
#include "chess/graphics/buffers/vertexarray.h"
#include "chess/graphics/buffers/indexbuffer.h"
#include "chess/graphics/renderable2d.h"
#include "chess/graphics/batchrenderer2d.h"
#include "chess/graphics/sprite.h"
/* #include "chess/utils/timer.h" */
#include "chess/graphics/uilayer.h"
#include "chess/graphics/group.h"
#include "chess/graphics/texture.h"
#include <FreeImage.h>

int main()
{
	using namespace Chess;
	using namespace Graphics;
	using namespace Maths;

	Window window("Chess", 960, 540);
	glClearColor(0, 0, 0, 1);

	Shader* shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	UILayer layer1(shader, -16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);

	srand(time(NULL));
    Texture* textures[] =
    {
        new Texture("res/textures/test.png"),
        new Texture("res/textures/test2.png"),
        new Texture("res/textures/test3.png")
    };

	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			if (rand() % 4)
				layer1.add(new Sprite(Maths::Vec2(x, y), Maths::Vec2(0.9f, 0.9f), textures[rand() % 3]));
			else
				layer1.add(new Sprite(Maths::Vec2(x, y), Maths::Vec2(0.9f, 0.9f), Maths::Vec4(1.0f, 0.0f, 0.0f, 1.0f)));
		}
	}

    GLint tex_ids[] = 
    {
        0, 1, 2
    };

    shader->enable();
    shader->set_uniform_1iv("textures", tex_ids, 3);

	/* Utils::Timer timer; */
	/* float secs = 0; */
	/* unsigned int frames = 0; */

	while (!window.closed())
	{
		window.clear();

		Vec2 mouse_pos = window.get_mouse_pos();
		Vec2 light_pos = Vec2(-16.0f + mouse_pos.x * (16.0f / 480.0f), 9.0f - mouse_pos.y * (9.0f / 270.0f));
		shader->enable();
		shader->set_uniform_2f("light_pos", light_pos);
		layer1.render();

        window.update();

		/* frames++; */
		/* if (timer.elapsed() > secs + 1.0f) */
		/* { */
		/* 	secs++; */
		/* 	std::cout << frames << " fps" << std::endl; */
		/* 	frames = 0; */
		/* } */
	}

    for (int i = 0; i < 3; i++)
        delete textures[i];
}
