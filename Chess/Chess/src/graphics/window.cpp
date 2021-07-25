#include "window.h"

namespace chess {
	namespace graphics {

		void window_resize(GLFWwindow* window, int width, int height);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		Window::Window(const char* title, int width, int height)
		{
			m_title = title;
			m_width = width;
			m_height = height;
			if (!init())
				glfwTerminate();
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW!" << std::endl;
			}

			m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
			if (!m_window)
			{
				std::cout << "Failed to initialize GLFW window!" << std::endl;
				return false;
			}

			glfwMakeContextCurrent(m_window);
			glfwSetWindowUserPointer(m_window, this);
			glfwSetWindowSizeCallback(m_window, window_resize);
			glfwSetKeyCallback(m_window, key_callback);
			glfwSetMouseButtonCallback(m_window, mouse_button_callback);
			glfwSetCursorPosCallback(m_window, cursor_position_callback);

			if (glewInit() != GLEW_OK) {
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			}

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
			return true;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update()
		{
			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_window);
		}

		int Window::get_width() const
		{
			return m_width;
		}

		int Window::get_height() const
		{
			return m_height;
		}

		bool Window::key_down(unsigned int keycode) const
		{
			if (keycode >= GLFW_KEY_LAST)
				return false;

			return m_keys[keycode];
		}

		bool Window::mouse_button_down(unsigned int button) const
		{
			if (button >= GLFW_MOUSE_BUTTON_LAST)
				return false;

			return m_mouse_buttons[button];
		}

		void Window::get_mouse_pos(double& x, double& y) const
		{
			x = m_cursor_x;
			y = m_cursor_y;
		}

		void window_resize(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_width = width;
			win->m_width = width;
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_keys[key] = action != GLFW_RELEASE;
		}
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_mouse_buttons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_cursor_x = xpos;
			win->m_cursor_y = ypos;
		}
	}
}
