#include "chess/graphics/window.h"
#include "chess/utils/file.h"
#include "chess/graphics/shader.h"
#include "chess/maths/maths.h"
#include <iostream> 
#include <chess/graphics/buffers/buffer.h>
#include <chess/graphics/buffers/vertexarray.h>
#include <chess/graphics/buffers/indexbuffer.h>

int main()
{
	using namespace Chess;
	using namespace Graphics;
	using namespace Maths;

	Window window("Chess", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);


	GLfloat vertices[] =
	{
		 0.0f,  0.0f,
		 0.5f,  0.0f,
		 0.5f,  0.5f,
		 0.0f,  0.5f,
	};

	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GLfloat colorsA[] =
	{
		1, 0, 1, 1,
		1, 0, 1, 1,
		1, 0, 1, 1,
		1, 0, 1, 1
	};

	GLfloat colorsB[] =
	{
		1.0f, 0.4f, 0.8f, 1.0f,
		1.0f, 0.4f, 0.8f, 1.0f,
		1.0f, 0.4f, 0.8f, 1.0f,
		1.0f, 0.4f, 0.8f, 1.0f,
	};

	VertexArray sprite1, sprite2;
	Buffer* vbo = new Buffer(vertices, 4 * 2, 2);
	IndexBuffer ibo(indices, 6);

	sprite1.add_buffer(new Buffer(vertices, 4 * 2, 2), 0);
	sprite1.add_buffer(new Buffer(colorsA, 4 * 4, 4), 1);
	sprite2.add_buffer(new Buffer(vertices, 4 * 2, 2), 0);
	sprite2.add_buffer(new Buffer(colorsB, 4 * 4, 4), 1);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();

	Mat4x4 ortho = Mat4x4::create_orthographic(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 1.0f);
	shader.set_uniform_mat4("pr_matrix", Mat4x4::identity);

	Mat4x4 trans = Mat4x4::create_translation(Vec3(0.5f, 0.5f, 0.0f));
	Mat4x4 rot = Mat4x4::create_rotation(-90.0f, Vec3(0, 0, 1));

	shader.set_uniform_4f("frag_color", Vec4(1.0f, 0.4f, 0.8f, 1.0f));

	while (!window.closed())
	{
		Vec2 mouse_pos = window.get_mouse_pos();
		Vec2 light_pos = Vec2((mouse_pos.x / 480.0f) - 1, 1 - (mouse_pos.y / 270.0f));
		shader.set_uniform_2f("light_pos", light_pos);
		window.clear();

		sprite1.bind();
		ibo.bind();
		shader.set_uniform_mat4("ml_matrix", Mat4x4::identity);
		glDrawElements(GL_TRIANGLES, ibo.get_count(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite1.unbind();

		sprite2.bind();
		ibo.bind();
		shader.set_uniform_mat4("ml_matrix", trans);
		glDrawElements(GL_TRIANGLES, ibo.get_count(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite2.unbind();

		window.update();
	}
}