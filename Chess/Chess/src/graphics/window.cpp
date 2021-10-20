#include "chess/graphics/window.h"

namespace Game 
{
	void window_resize(GLFWwindow* window, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	Window::Window(const char* title, const Vec2i& size, const Vec2i& aspect)
		: m_title(title), m_size(size), m_window(nullptr), m_aspect(aspect)
	{
		for (int i = 0; i < GLFW_KEY_LAST; i++)
			m_keys[i] = false;

		for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
			m_mouse_buttons[i] = false;

		for (int i = 0; i < GLFW_KEY_LAST; i++)
			m_keys[i] = false;
	}

	bool Window::init()
	{
		m_window = glfwCreateWindow(m_size.x, m_size.y, m_title, NULL, NULL);
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
		glfwSwapInterval(0); // Disable VSync
		glfwSetWindowAspectRatio(m_window, m_aspect.x, m_aspect.y);

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

	Vec2i Window::get_size() const
	{
		return m_size;
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

	const Vec2 Window::get_mouse_pos() const
	{
		return m_mouse_pos;
	}
	
	void Window::add_window_resize_listener(IWindowResizeListener* listener)
	{
		m_resize_listeners.push_back(listener);
	}

	void Window::on_resize(const Vec2i& new_size)
	{
		m_size = new_size;

		for (auto listener : m_resize_listeners)
			listener->on_resize(new_size);
	}

	void window_resize(GLFWwindow* window, int width, int height)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->on_resize(Vec2i(width, height));
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
		win->m_mouse_pos.x = (float)xpos;
		win->m_mouse_pos.y = (float)ypos;
	}
}
