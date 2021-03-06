#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "chess/maths/maths.h"
#include <vector>
#include "iwindowresizelistener.h"

namespace Game
{
	class Window
	{
	private:
		GLFWwindow* m_window;
		const char* m_title;
		Vec2i m_size;
		Vec2i m_aspect;
		bool m_keys[GLFW_KEY_LAST];
		bool m_mouse_buttons[GLFW_MOUSE_BUTTON_LAST];
		Vec2 m_mouse_pos;
		std::vector<IWindowResizeListener*> m_resize_listeners;

	public:
		Window(const char* title, const Vec2i& size, const Vec2i& aspect);

		bool init();
		void clear() const;	
		void update();
		bool closed() const;

		Vec2i get_size() const;

		bool key_down(unsigned int keycode) const;
		bool mouse_button_down(unsigned int button) const;
		const Vec2 get_mouse_pos() const;

		void add_window_resize_listener(IWindowResizeListener* listener);

	private:
		void on_resize(const Vec2i& new_size);
		friend void window_resize(GLFWwindow* window, int width, int height);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};
}
