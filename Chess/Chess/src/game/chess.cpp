#include "chess/game/chess.h"
#include <iostream> 
#include "chess/maths/maths.h"
#include "chess/graphics/batchrenderer2d.h"
#include "chess/graphics/sprite.h"
#include "chess/utils/timer.h"
#include "chess/graphics/layer.h"
#include "chess/graphics/fontatlas.h"
#include "chess/graphics/label.h"

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

            Graphics::TextureArray sprite_array(3, Maths::Vec2(8, 8), GL_RGB, GL_BGR, 4);
            Graphics::TextureArray::Element textures[] = 
            {
                sprite_array.add("res/textures/test.png"),
                sprite_array.add("res/textures/test2.png"),
                sprite_array.add("res/textures/test3.png")
            };

            Graphics::Layer sprite_layer(sprite_array.get_id(), sprite_shader, 
                    Maths::Mat4x4::create_orthographic(0.0f, 320.0f, 0.0f, 180.0f, -1.0f, 1.0f));

            Maths::Vec2 atlas_size = m_font_atlas->get_size();
            unsigned char* atlas_pixels = m_font_atlas->get_pixels();
            Graphics::TextureArray text_array(1, atlas_size, GL_RED, GL_RED, 1);
            Graphics::TextureArray::Element font_texture = text_array.add(atlas_pixels, (int)atlas_size.x, (int)atlas_size.y);

            Graphics::Layer text_layer(text_array.get_id(), text_shader, 
                    Maths::Mat4x4::create_orthographic(0.0f, 320.0f, 0.0f, 180.0f, -1.0f, 1.0f));

            srand((unsigned int)time(NULL));

            /* for (float y = 0.0f; y < 180.0f; y+= 8.0f) */
            /* { */
            /*     for (float x = 0.0f; x < 320.0f; x += 8.0f) */
            /*     { */
            /*         if (rand() % 4) */
            /*             sprite_layer.add(new Graphics::Sprite(Maths::Vec2(x, y), Maths::Vec2(8.0f, 8.0f), */ 
            /*                         textures[rand() % 3])); */
            /*         else */
            /*             sprite_layer.add(new Graphics::Sprite(Maths::Vec2(x, y), Maths::Vec2(8.0f, 8.0f), */ 
            /*                         Maths::Vec4(1.0f, 0.0f, 0.0f, 1.0f))); */
            /*     } */
            /* } */

            Graphics::Label* l1 = new Graphics::Label(m_font_atlas, font_texture, "test", Maths::Vec2(50.0f, 50.0f), Maths::Vec2(20.0f, 20.0f), Maths::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

            text_layer.add(l1);

            sprite_shader->enable();
            sprite_shader->set_uniform_1i("textures", 0);

            Utils::Timer timer;
            float secs = 0;
            unsigned int frames = 0;

            while (!m_window->closed())
            {
                m_window->clear();

                Maths::Vec2 mouse_pos = m_window->get_mouse_pos();
                Maths::Vec2 light_pos = Maths::Vec2(-16.0f + mouse_pos.x * (16.0f / 480.0f), 
                        9.0f - mouse_pos.y * (9.0f / 270.0f));
                sprite_shader->enable();
                sprite_shader->set_uniform_2f("light_pos", light_pos);
                sprite_layer.render();
                text_layer.render();
                m_window->update();

                frames++;
                if (timer.elapsed() / 1000.0f > secs + 1.0f)
                {
                    secs++;
                    //std::cout << frames << " fps" << std::endl;
                    frames = 0;
                }
            }

            delete sprite_shader;
            delete text_shader;
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

