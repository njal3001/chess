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

namespace Game
{
    void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id,
        GLenum severity, GLsizei length, const GLchar* message, const void* user_param);

    Chess::Chess()
        :  m_turn(Color::White), m_window(nullptr), m_resource_manager(nullptr), 
            m_board(nullptr), m_selected(nullptr), m_prev_mouse_pressed(false)
    {}

    bool Chess::init()
    {
        if (!glfwInit())
        {
            std::cout << "Failed to initialize GLFW!" << std::endl;
            return false;
        }

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        m_window = new Window("Chess", 512, 512);
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

        m_resource_manager = new ResourceManager();
        if (!m_resource_manager->init())
        {
            std::cout << "Could not initialize Resource Manager!" << std::endl;
            return false;
        }

        m_board = new Board(Vec2(0, 0), Vec2(1, 1), m_resource_manager);

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

        Timer timer;
        float secs = 0;
        unsigned int frames = 0;

        m_valid_moves = m_board->valid_moves(m_turn);
        update_piece_sprites();

        while (!m_window->closed())
        {
            render();

            if (check_click())
            {
                Vec2i clicked_pos = moused_square();
                Piece* clicked_piece = m_board->get_piece(clicked_pos);

                std::cout << "Turn: " << (int)m_turn << std::endl;
                std::cout << "Clicked square: " << clicked_pos << std::endl;

                if (clicked_piece && clicked_piece->get_color() == m_turn)
                {
                    m_selected = clicked_piece;
                    m_selected_pos = clicked_pos;

                    std::cout << "Valid moves: " << std::endl;
                    for (auto& move : m_valid_moves[clicked_piece]) 
                        std::cout << move.new_pos << std::endl;
                }
                else if (m_selected)
                {
                    for (auto& move : m_valid_moves[m_selected]) 
                    {
                        if (move.new_pos == clicked_pos)
                        {
                            std::string hash = create_state_hash();
                            if (m_board->move_piece(m_selected_pos, move))
                            {
                                m_turn = opposite(m_turn);
                                m_selected = nullptr;
                                m_history.push_back(hash);

                                m_valid_moves = m_board->valid_moves(m_turn);
                                update_piece_sprites();

                                bool no_valid_moves = true;
                                for (auto iter = m_valid_moves.begin(); iter != m_valid_moves.end(); iter++)
                                {
                                    const std::vector<Move>& valid_moves = iter->second;
                                    if (valid_moves.size() > 0)
                                    {
                                        no_valid_moves = false;
                                        break;
                                    }
                                }

                                if (no_valid_moves)
                                {
                                    if (m_board->king_threatened(m_turn))
                                        std::cout << "Checkmate!" << std::endl;
                                    else 
                                        std::cout << "Stalemate!" << std::endl;
                                }
                            }


                            break;
                        }
                    }
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

        m_resource_manager->get_game_layer()->render();

        m_window->update();
    }

    void Chess::update_piece_sprites() const
    {
        std::unordered_map<Piece*, Vec2i> pieces = m_board->get_pieces();
        for (auto iter = pieces.begin(); iter != pieces.end(); iter++)
        {
            Piece* piece = iter->first;
            const Vec2i& pos = iter->second;
            if (m_board->in_bound(pos))
            {
                piece->get_sprite()->hidden = false;
                piece->get_sprite()->position = Vec3(pos.x * 8, 56 - pos.y * 8, 0);
            }
            else
            {
                piece->get_sprite()->hidden = true;
            }
        }
    }

    Vec2i Chess::moused_square() const
    {
        Vec2 mouse_pos = m_window->get_mouse_pos();
        int x = (int)(mouse_pos.x / 64);
        int y = (int)(mouse_pos.y / 64);
        return Vec2i(x, y);
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

    std::string Chess::create_state_hash()
    {
        std::string hash;
        for (int y = 0; y < 8; y++)
            for (int x = 0; x < 8; x++)
            {
                Piece* piece = m_board->get_piece(Vec2i(x, y));
                if (piece)
                    hash += piece->get_id();
                else
                    hash += (char)0;
            }
        
        return hash;
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
