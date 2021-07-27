#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chess/maths/vec2.h>

namespace Chess 
{
	namespace Graphics
	{
		using namespace Maths;

		class Window
		{
		private:
			GLFWwindow* m_window;
			const char* m_title;
			int m_width, m_height;
			bool m_keys[GLFW_KEY_LAST];
			bool m_mouse_buttons[GLFW_MOUSE_BUTTON_LAST];
			double m_cursor_x, m_cursor_y;

		public:
			Window(const char* title, int width, int height);
			~Window();
			void clear() const;
			void update();
			bool closed() const;

			int get_width() const;
			int get_height() const;

			bool key_down(unsigned int keycode) const;
			bool mouse_button_down(unsigned int button) const;
			Vec2 get_mouse_pos() const;

		private:
			bool init();
			friend void window_resize(GLFWwindow* window, int width, int height);
			friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}

