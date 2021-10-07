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
#include <algorithm>

namespace Chess
{
    namespace Game
    {
		void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id,
			GLenum severity, GLsizei length, const GLchar* message, const void* user_param);

        Chess::Chess()
            :  m_turn(Piece::Color::white), m_window(nullptr), m_resource_manager(nullptr), 
                m_board(nullptr), m_selected(nullptr)
        {}

        bool Chess::init()
        {
			if (!glfwInit())
            {
				std::cout << "Failed to initialize GLFW!" << std::endl;
                return false;
            }

			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

            m_window = new Graphics::Window("Chess", 512, 512);
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

            m_resource_manager = new Graphics::ResourceManager();
            if (!m_resource_manager->init())
            {
                std::cout << "Could not initialize Resource Manager!" << std::endl;
                return false;
            }

            m_board = new Board(Maths::Vec2(0, 0), Maths::Vec2(1, 1), m_resource_manager->get_sprite_array());
            m_resource_manager->get_game_layer()->add(m_board->get_group());

            srand((unsigned int)time(NULL));

            return true;
        }

        Chess::~Chess()
        {
            delete m_board;
            delete m_resource_manager;
            delete m_window;
			glfwTerminate();
        }

        void Chess::run()
        {

            Utils::Timer timer;
            float secs = 0;
            unsigned int frames = 0;

            while (!m_window->closed())
            {
                render();

                if (check_click())
                {
                    Maths::Vec2i pos = moused_square();
                    const Piece* clicked_piece = m_board->get_piece(pos);

                    std::cout << "Turn: " << m_turn << std::endl;
                    std::cout << "Clicked square: " << pos << std::endl;

                    if (clicked_piece && clicked_piece->get_color() == m_turn)
                    {
                        select_piece(clicked_piece);

                        std::cout << "Valid moves: " << std::endl;
                        for (auto move : clicked_piece->valid_moves()) 
                            std::cout << move << std::endl;
                    }
                    else if (m_selected)
                    {
                        if (m_board->move_piece(m_selected->get_pos(), pos)) {
                            m_turn = Piece::opposite(m_turn);
                        }

                        select_piece(nullptr);
                    }
                }

                // frames++;
                // if (timer.elapsed() / 1000.0f > secs + 1.0f)
                // {
                //     secs++;
                //     std::cout << frames << " fps" << std::endl;
                //     frames = 0;
                // }
            } 
        }

        void Chess::render() const
        {
            m_window->clear();

            m_resource_manager->get_sprite_shader()->enable();
            m_resource_manager->get_game_layer()->render();

            m_window->update();
        }

        Maths::Vec2i Chess::moused_square() const
        {
            Maths::Vec2 mouse_pos = m_window->get_mouse_pos();
            int x = (int)(mouse_pos.x / 64);
            int y = (int)(mouse_pos.y / 64);
            return Maths::Vec2i(x, y);
        }

        bool Chess::check_click()
        {
            bool val = false;
            bool pressed = m_window->mouse_button_down(0);

            if (pressed && !m_prev_mouse_pressed) 
                val = true;
            
            m_prev_mouse_pressed = pressed;

            return val;
        }

        void Chess::select_piece(const Piece* piece)
        {
            m_selected = piece;
            if (piece)
                m_valid_moves = piece->valid_moves();
            else
                m_valid_moves.clear();
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

