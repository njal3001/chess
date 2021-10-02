#include "chess/game/chess.h"
#include <iostream> 
#include "chess/maths/maths.h"
#include "chess/graphics/batchrenderer2d.h"
#include "chess/graphics/sprite.h"
#include "chess/utils/timer.h"
#include "chess/graphics/layer.h"
#include "chess/graphics/fontatlas.h"
#include "chess/graphics/label.h"
#include "chess/game/board.h"

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

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

            m_font_atlas = new Graphics::FontAtlas("res/fonts/upheavtt.ttf", 20, Maths::Vec2(256, 128));
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

            Graphics::Shader* sprite_shader = new Graphics::Shader("res/shaders/sprite.vert",
                    "res/shaders/sprite.frag");

            Graphics::Shader* text_shader = new Graphics::Shader("res/shaders/text.vert",
                "res/shaders/text.frag");

            
            auto* sprite_array = new Graphics::TextureArray(3, Maths::Vec2(64, 64), GL_RGB, GL_RGBA, 4);
            Graphics::Layer game_layer(sprite_array->get_id(), sprite_shader, 
                    Maths::Mat4x4::create_orthographic(0.0f, 320.0f, 0.0f, 180.0f, -1.0f, 1.0f));

            Board board(Maths::Vec2(), sprite_array);
            game_layer.add(board.get_group());

            Maths::Vec2 atlas_size = m_font_atlas->get_size();
            unsigned char* atlas_pixels = m_font_atlas->get_pixels();
            Graphics::TextureArray text_array(1, atlas_size, GL_RED, GL_RED, 1);
            Graphics::TextureArray::Element font_texture = text_array.add(atlas_pixels, (int)atlas_size.x, (int)atlas_size.y);

            Graphics::Layer text_layer(text_array.get_id(), text_shader, 
                    Maths::Mat4x4::create_orthographic(0.0f, 320.0f, 0.0f, 180.0f, -1.0f, 1.0f));

            srand((unsigned int)time(NULL));

            Utils::Timer timer;
            float secs = 0;
            unsigned int frames = 0;

            while (!m_window->closed())
            {
                m_window->clear();

                Maths::Vec2 mouse_pos = m_window->get_mouse_pos();
                sprite_shader->enable();
                game_layer.render();

                m_window->update();

                frames++;
                if (timer.elapsed() / 1000.0f > secs + 1.0f)
                {
                    secs++;
                    std::cout << frames << " fps" << std::endl;
                    frames = 0;
                }
            } 

            delete sprite_shader;
            delete text_shader;
            delete sprite_array;
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

