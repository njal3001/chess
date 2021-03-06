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
            m_board(nullptr), m_selected(nullptr), m_prev_mouse_pressed{false, false}, 
            m_game_state(GameState::Menu), m_board_flipped(false), m_is_promoting(false),
            m_white_promotion_sprite(nullptr), m_black_promotion_sprite(nullptr), m_is_dragging(false)
    {}

    bool Chess::init()
    {
        if (!glfwInit())
        {
            std::cout << "Failed to initialize GLFW!" << std::endl;
            return false;
        }

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        m_window = new Window("Chess", Vec2i(512, 512), Vec2i(1, 1));
        if (!m_window->init())
        {
            std::cout << "Could not initialize Window!" << std::endl;
            return false;
        }

        m_window->add_window_resize_listener(this);

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

        TextureArray::Element white_promotion_tex = m_resource_manager->get_sprite_array()->add("res/textures/WhitePromotion.png");
        TextureArray::Element black_promotion_tex = m_resource_manager->get_sprite_array()->add("res/textures/BlackPromotion.png");
        m_white_promotion_sprite = new Sprite(Vec2(), Vec2(8, 32), white_promotion_tex);
        m_black_promotion_sprite = new Sprite(Vec2(), Vec2(8, 32), black_promotion_tex);
        m_white_promotion_sprite->hidden = true;
        m_black_promotion_sprite->hidden = true;
        m_resource_manager->get_game_layer()->add(m_white_promotion_sprite);
        m_resource_manager->get_game_layer()->add(m_black_promotion_sprite);

        m_can_move_tex = m_resource_manager->get_sprite_array()->add("res/textures/CanMove.png");

        m_main_text = new Label(m_resource_manager->get_font_atlas(), m_resource_manager->get_font_texture(), "Chess",
            Vec3(12.0f, 40.0f, 1.0f), Vec2(7.0f, 7.0f), Vec4(223.0f/255.0f, 113.0f/255.0f, 38.0f/255.0f, 1.0f));

        m_support_text = new Label(m_resource_manager->get_font_atlas(), m_resource_manager->get_font_texture(), "Click to begin",
            Vec3(5.0f, 34.0f, 1.0f), Vec2(3.0f, 3.0f), Vec4(223.0f/255.0f, 113.0f/255.0f, 38.0f/255.0f, 1.0f));
        
        m_resource_manager->get_text_layer()->add(m_main_text);
        m_resource_manager->get_text_layer()->add(m_support_text);

        return true;
    }

    Chess::~Chess()
    {
        delete m_board;
        delete m_resource_manager;
        delete m_window;
        glfwTerminate();
    }

    void Chess::on_resize(const Vec2i& new_size)
    {
        Vec2i window_size = m_window->get_size();

        Vec2i scene_size = window_size; 
        if (window_size.x > window_size.y)
        {
            scene_size.x = window_size.y;
        }
        else
        {
            scene_size.y = window_size.x;
        }

        Vec2 offset = Vec2((window_size.x - scene_size.x) / 2.0f, (window_size.y - scene_size.y) / 2.0f);
        glViewport(offset.x, offset.y, scene_size.x, scene_size.y);
    }

    Vec2 Chess::window_to_world_pos(const Vec2& pos) const
    {
        Vec2i window_size = m_window->get_size();

        Vec2i scene_size = window_size; 
        if (window_size.x > window_size.y)
        {
            scene_size.x = window_size.y;
        }
        else
        {
            scene_size.y = window_size.x;
        }

        Vec2 offset = Vec2((window_size.x - scene_size.x) / 2.0f, (window_size.y - scene_size.y) / 2.0f);
        Vec2 shifted_pos = pos - offset;

        return Vec2((shifted_pos.x * 64) / scene_size.x, (shifted_pos.y * 64) / scene_size.y);
    }

    void Chess::run()
    {
        Timer timer;
        float secs = 0;
        unsigned int frames = 0;

        new_turn(Color::White, false);

        while (!m_window->closed())
        {
            render();
            
            if (m_game_state == GameState::Menu)
            {
                if (check_click(0))
                {
                    m_main_text->hidden = true;
                    m_support_text->hidden = true;
                    m_game_state = GameState::Playing;
                }
            }
            else if (m_game_state == GameState::Playing)
            {
                do_turn();
            }
            else if (m_game_state == GameState::Promoting)
            {
                if (check_click(1))
                {
                    m_board->reset_to_prev_state();
                    m_selected = nullptr;
                    update_piece_sprites();

                    m_game_state = GameState::Playing;
                    hide_promotion_sprites();
                }
                else if (check_click(0))
                {
                    Vec2i clicked_pos = moused_square();
                    int y_diff = abs(clicked_pos.y - m_selected_pos.y);
                    if (clicked_pos.x != m_selected_pos.x || y_diff > 3)
                    {
                        m_board->reset_to_prev_state();
                        update_piece_sprites();
                        m_selected_pos = m_board->get_pos(m_selected);
                    }
                    else
                    {
                        Piece* promotion = nullptr;
                        switch (y_diff) 
                        {
                            case 0:
                                promotion = new Queen(m_selected_pos, m_turn, m_board);
                                break;
                            case 1:
                                promotion = new Bishop(m_selected_pos, m_turn, m_board);
                                break;
                            case 2:
                                promotion = new Knight(m_selected_pos, m_turn, m_board);
                                break;
                            case 3:
                                promotion = new Rook(m_selected_pos, m_turn, m_board);
                                break;
                        }

                        m_board->promote(m_selected_pos, promotion);
                        new_turn(opposite(m_turn));
                    }

                    m_game_state = GameState::Playing;
                    hide_promotion_sprites();
                }
            }
            else if (m_game_state != GameState::GameOver)
            {
                m_main_text->text = "Game Over";
                m_main_text->position = Vec3(6.0f, 40.0f, 1.0f);
                m_main_text->size = Vec2(5.0f, 5.0f);
                m_support_text->position = Vec3(9.0f, 34.0f, 1.0f);

                switch (m_game_state)
                {
                case GameState::Checkmate:
                    m_support_text->text = get_color_string(opposite(m_turn)) + " won by\n  checkmate!";
                    break;
                
                case GameState::Stalemate:
                    m_support_text->text = "   Draw by\n  stalemate";
                    break;
                }

                m_main_text->hidden = false;
                m_support_text->hidden = false;
                m_game_state = GameState::GameOver;
            }
            
            frames++;
            if (timer.elapsed() / 1000.0f > secs + 1.0f)
            {
                secs++;
                std::cout << frames << " fps" << std::endl;
                frames = 0;
            }
        } 
    }


    void Chess::do_turn()
    {
        if (check_click(1) && m_selected)
        {
            m_is_dragging = false;
            deselect();
            return;
        }

        Vec2i moused_pos = moused_square();
        Piece* moused_piece = m_board->get_piece(moused_pos);

        if (check_click(0))
        {
            if (try_move(moused_pos))
                return;
            
            if (moused_piece && moused_piece->get_color() == m_turn)
            {
                m_selected = moused_piece;
                m_selected_pos = moused_pos;
                m_is_dragging = true;
            }
        }
        else if (m_is_dragging && !m_window->mouse_button_down(0))
        {
            try_move(moused_pos);
            stop_drag();
        }
    }
    
    bool Chess::try_move(const Vec2i& target_pos)
    {
        if (!m_selected)
            return false;

        if (m_selected->check_castle(m_selected_pos, target_pos))
        {
            m_board->castle(m_turn, Calc::sgn(target_pos.x - m_selected_pos.x));
            new_turn(opposite(m_turn));
        }
        else
        {
            for (auto& move : m_valid_moves[m_selected]) 
            {
                if (move.new_pos == target_pos)
                {
                    if (m_board->move_piece(m_selected_pos, move))
                    {
                        if (m_selected->check_promote(target_pos))
                        {
                            m_selected_pos = target_pos;
                            m_game_state = GameState::Promoting;
                            update_piece_sprites();
                            show_promotion_sprite(m_selected_pos, m_turn);
                        }
                        else
                        {
                            new_turn(opposite(m_turn));
                        }

                        return true;
                    }
                }
            }
        }

        return false;
    }
    
    void Chess::stop_drag()
    {
        if (m_is_dragging && m_selected)
        {
            m_is_dragging = false;
            Vec2 sprite_pos = Vec2(m_selected_pos.x * 8, 56 - m_selected_pos.y * 8);
            update_piece_sprite(m_selected, sprite_pos);
        }

    }
    
    void Chess::new_turn(Color turn, bool flip)
    {
        m_turn = turn;
        std::string hash = m_board->create_state_hash();
        m_selected = nullptr;
        m_board->push_history(hash);

        m_valid_moves = m_board->valid_moves(m_turn);

        if (flip)
            flip_board();
        update_piece_sprites();

        m_game_state = check_game_state();
    }

    void Chess::deselect()
    {
        if (!m_selected) return;

        Vec2 sprite_pos = Vec2(m_selected_pos.x * 8, 56 - m_selected_pos.y * 8);
        update_piece_sprite(m_selected, sprite_pos);

        m_selected = nullptr;
    }

    void Chess::render()
    {
        m_window->clear();

        if (m_is_dragging && m_selected)
        {
            Sprite* sprite = m_selected->get_sprite();
            Vec2 mouse_pos = m_window->get_mouse_pos();
            Vec2 world_pos = window_to_world_pos(mouse_pos);

            float y = 0;
            if (!m_board_flipped) 
            {
                y = 64 - world_pos.y - 4;
            }
            else
            {
                y = world_pos.y - 4;
            }

            Vec2 sprite_pos = Vec2(world_pos.x - 4, y);
            update_piece_sprite(m_selected, sprite_pos);
        }

        if (m_game_state == GameState::Playing)
        {
            if (m_selected)
            {
                float y = m_turn == Color::White ? 56 - m_selected_pos.y * 8 : m_selected_pos.y * 8;
                Vec3 highlight_pos = Vec3(m_selected_pos.x * 8, y, 0.1f);
                BatchRenderer2D* renderer = m_resource_manager->get_game_layer()->get_renderer();

                Sprite highlight(highlight_pos, Vec2(8, 8), Vec4(153.0f/255.0f, 229.0f/255.0f, 80.0f/255.0f, 1.0f));
                highlight.submit(renderer);

                for (auto& move : m_valid_moves[m_selected])
                {
                    float y = m_turn == Color::White ? 56 - move.new_pos.y * 8 : move.new_pos.y * 8;
                    Vec3 move_highlight_pos = Vec3(move.new_pos.x * 8, y, 0.6f);
                    Sprite move_highlight(move_highlight_pos, Vec2(8, 8), m_can_move_tex);
                    move_highlight.submit(renderer);
                }
            }
        }

        m_resource_manager->get_game_layer()->render();
        m_resource_manager->get_text_layer()->render();

        m_window->update();
    }
    
    void Chess::update_piece_sprites() const
    {
        std::unordered_map<Piece*, Vec2i> pieces = m_board->get_pieces();
        for (auto iter = pieces.begin(); iter != pieces.end(); iter++)
        {
            Piece* piece = iter->first;
            Sprite* sprite = piece->get_sprite();
            const Vec2i& pos = iter->second;

            if (m_board->in_bound(pos))
            {
                sprite->hidden = false;
                Vec2 sprite_pos = Vec2(pos.x * 8, 56 - pos.y * 8);

                update_piece_sprite(piece, sprite_pos);
            }
            else
            {
                sprite->hidden = true;
            }
        }
    }

    void Chess::update_piece_sprite(Piece* piece, const Vec2& sprite_pos) const
    {
        if (m_board_flipped)
        {
            Mat4x4 transform = Mat4x4::create_translation(Vec3(sprite_pos.x + 4, sprite_pos.y + 4, 0));
            transform *= Mat4x4::create_rotation(180, Vec3(0, 0, 1));
            transform *= Mat4x4::create_rotation(180, Vec3(0, 1, 0));
            transform *= Mat4x4::create_translation(Vec3(-sprite_pos.x - 4, -sprite_pos.y - 4, 0));
            piece->get_sprite()->transform = transform;
        }
        else 
        {
            piece->get_sprite()->transform = Mat4x4::identity;
        }

        piece->get_sprite()->position.x = sprite_pos.x;
        piece->get_sprite()->position.y = sprite_pos.y;

        float z = piece->get_color() == m_turn ? 0.5 : 0.25;
        piece->get_sprite()->position.z = z;
    }

    Vec2i Chess::moused_square() const
    {
        Vec2 mouse_pos = m_window->get_mouse_pos();
        Vec2 world_pos = window_to_world_pos(mouse_pos);

        int x = (int)(world_pos.x / 8);
        int y = (int)(world_pos.y / 8);

        if (m_board_flipped)
            y = 7 - y;

        return Vec2i(x, y);
    }

    bool Chess::check_click(int button)
    {
        bool val = false;
        bool pressed = m_window->mouse_button_down(button);

        if (pressed && !m_prev_mouse_pressed[button]) 
            val = true;
        
        m_prev_mouse_pressed[button] = pressed;

        return val;
    }


    Chess::GameState Chess::check_game_state() const
    {
        if (m_game_state == GameState::Menu)
            return GameState::Menu;

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
                return GameState::Checkmate;
            else 
                return GameState::Stalemate;
        }

        return GameState::Playing;
    }

    std::string Chess::get_color_string(Color color) const
    {
        return color == Color::White ? "White" : "Black";
    }
    
    void Chess::flip_board()
    {
        Group* board_group = m_board->get_group();
        board_group->transform(Mat4x4::create_translation(Vec3(32.0f, 32.0f, 0.0f)));
        board_group->transform(Mat4x4::create_rotation(180.0f, Vec3(0.0f, 0.0f, 1.0f)));
        board_group->transform(Mat4x4::create_rotation(180.0f, Vec3(0.0f, 1.0f, 0.0f)));
        board_group->transform(Mat4x4::create_translation(Vec3(-32.0f, -32.0f, 0.0f)));

        m_board_flipped = !m_board_flipped;
    }
    
    void Chess::show_promotion_sprite(const Vec2i& square, Color color)
    {
        Sprite* sprite = color == Color::White ? m_white_promotion_sprite : m_black_promotion_sprite;
        sprite->position = Vec3(square.x * 8, 32, 1);
        sprite->hidden = false;
    }

    void Chess::hide_promotion_sprites()
    {
        m_white_promotion_sprite->hidden = true;
        m_black_promotion_sprite->hidden = true;
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
