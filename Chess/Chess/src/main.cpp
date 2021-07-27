#include "chess/graphics/window.h"
#include "chess/utils/file.h"
#include "chess/graphics/shader.h"
#include "chess/maths/maths.h"
#include <iostream> 

int main()
{
	using namespace Chess;
	using namespace Graphics;
	using namespace Maths;

	Window window("Chess", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);


	GLfloat vertices[] =
	{
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f,
	};

	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();

	Mat4x4 ortho = Mat4x4::create_orthographic(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 1.0f);
	shader.set_uniform_mat4("pr_matrix", Mat4x4::identity);

	Mat4x4 trans = Mat4x4::create_translation(Vec3(0.5f, 1.0f, 0.0f));
	Mat4x4 rot = Mat4x4::create_rotation(-90.0f, Vec3(0, 0, 1));
	//shader.set_uniform_mat4("ml_matrix", trans * rot);

	shader.set_uniform_2f("light_pos", Vec2(0.0f, -0.1f));
	shader.set_uniform_4f("frag_color", Vec4(1.0f, 0.4f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.clear();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.update();
	}
}