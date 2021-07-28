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

int main()
{
	using namespace Chess;
	using namespace Graphics;
	using namespace Maths;

	Window window("Chess", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();

	shader.set_uniform_mat4("pr_matrix", Mat4x4::create_orthographic(-15, 15, -15, 15, -1, 1));

	Renderable2D sprite1(Vec3(5, 5, 0), Vec2(10, 15), Vec4(1, 0, 1, 1), shader);
	Renderable2D sprite2(Vec3(-12, -5, 0), Vec2(15, 10), Vec4(0.2f, 0, 1, 1), shader);
	SimpleRenderer2D renderer;

	while (!window.closed())
	{
		window.clear();

		Vec2 mouse_pos = window.get_mouse_pos();
		Vec2 light_pos = Vec2(15 * (mouse_pos.x / 480.0f) - 15, 15 - 15 * (mouse_pos.y / 270.0f));
		shader.set_uniform_2f("light_pos", light_pos);
		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.flush();

		window.update();
	}
}