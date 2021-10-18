#pragma once
#include "chess/graphics/window.h"
#include "chess/graphics/resourcemanager.h"
#include "board.h"

namespace Game
{

    class Chess
    {
    private:
        enum class GameState
        {
            Playing,
            Checkmate,
            Stalemate,
        };
    
    private:
        Window* m_window;
        ResourceManager* m_resource_manager;

        Color m_turn;
        Piece* m_selected;
        Vec2i m_selected_pos;
        Board* m_board;
        bool m_board_flipped;
        GameState m_game_state;
        std::unordered_map<Piece*, std::vector<Move>> m_valid_moves;
        
        bool m_prev_mouse_pressed;

    public:
        Chess();
        ~Chess();

        bool init();
        void run();

    private:
        void do_turn();
        void flip_board();
        void render() const;
        void update_piece_sprites() const;

        Vec2i moused_square() const;
        bool check_click();
        GameState check_game_state() const;
        std::string get_color_string(Color color) const;
        void new_turn(Color turn, bool flip = true);

        // Declare outside of class instead?
        friend void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id,
            GLenum severity, GLsizei length, const GLchar* message, const void* user_param);
    };
}
