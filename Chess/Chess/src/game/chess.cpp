#include "chess/game/chess.h"
#include <iostream> 
#include "chess/maths/maths.h"
#include "chess/graphics/batchrenderer2d.h"
#include "chess/graphics/sprite.h"
#include "chess/utils/timer.h"
#include "chess/graphics/layer.h"
#include "chess/graphics/fontatlas.h"

namespace Chess
{
    namespace Game
    {
		void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id,
			GLenum severity, GLsizei length, const GLchar* message, const void* user_param);

        Chess::Chess()
            : m_window(nullptr), m_font_atlas(nullptr)
        {}

        bool Chess::init()
        {
			if (!glfwInit())
            {
				std::cout << "Failed to initialize GLFW!" << std::endl;
                return false;
            }

			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

            m_window = new Graphics::Window("Chess", 960, 540);
            if (!m_window->init())
            {
                std::cout << "Could not initialize Window!" << std::endl;
                return false;
            }

			if (glewInit() != GLEW_OK)
            {
				std::cout << "Could not initialize GLEW!" << std::endl;
                return false;
            }

            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(gl_debug_callback, NULL);

	        glClearColor(0, 0, 0, 1);

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

            m_font_atlas = new Graphics::FontAtlas("res/fonts/39335_UniversCondensed.ttf", 8);
            if (!m_font_atlas->init())
            {
                std::cout << "Could not initialize font atlas!" << std::endl;
                return false;
            }

            return true;
        }

        Chess::~Chess()
        {
            delete m_window;
            delete m_font_atlas;
			glfwTerminate();
        }

        void Chess::run()
        {

            Graphics::Shader* shader = new Graphics::Shader("res/shaders/basic.vert",
                    "res/shaders/basic.frag");

            Graphics::TextureArray texture_array(32, Maths::Vec2(8, 8));
            Graphics::TextureArray::Element textures[] = 
            {
                texture_array.add("res/textures/test.png"),
                texture_array.add("res/textures/test2.png"),
                texture_array.add("res/textures/test3.png")
            };

            Graphics::Layer layer1(texture_array.get_id(), shader, 
                    Maths::Mat4x4::create_orthographic(0.0f, 320.0f, 0.0f, 180.0f, -1.0f, 1.0f));

            srand((unsigned int)time(NULL));

            for (float y = 0.0f; y < 180.0f; y+= 8.0f)
            {
                for (float x = 0.0f; x < 320.0f; x += 8.0f)
                {
                    if (rand() % 4)
                        layer1.add(new Graphics::Sprite(Maths::Vec2(x, y), Maths::Vec2(8.0f, 8.0f), 
                                    textures[rand() % 3]));
                    else
                        layer1.add(new Graphics::Sprite(Maths::Vec2(x, y), Maths::Vec2(8.0f, 8.0f), 
                                    Maths::Vec4(1.0f, 0.0f, 0.0f, 1.0f)));
                }
            }

            shader->enable();
            shader->set_uniform_1i("textures", 0);

            Utils::Timer timer;
            float secs = 0;
            unsigned int frames = 0;

            while (!m_window->closed())
            {
                m_window->clear();

                Maths::Vec2 mouse_pos = m_window->get_mouse_pos();
                Maths::Vec2 light_pos = Maths::Vec2(-16.0f + mouse_pos.x * (16.0f / 480.0f), 
                        9.0f - mouse_pos.y * (9.0f / 270.0f));
                shader->enable();
                shader->set_uniform_2f("light_pos", light_pos);
                layer1.render();

                m_window->update();

                frames++;
                if (timer.elapsed() / 1000.0f > secs + 1.0f)
                {
                    secs++;
                    std::cout << frames << " fps" << std::endl;
                    frames = 0;
                }
            }
        }

		void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id,
			GLenum severity, GLsizei length, const GLchar* message, const void* user_param)
		{
            if (type == GL_DEBUG_TYPE_ERROR)
            {
			    fprintf(stderr, "GL CALLBACK: ** GL ERROR ** type = 0x%x, severity = 0x%x, message = %s\n",
				    type, severity, message);
            }
		}
    }
}

