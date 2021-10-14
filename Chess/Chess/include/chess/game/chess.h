#pragma once
#include "chess/graphics/window.h"
#include "chess/graphics/resourcemanager.h"
#include "board.h"

namespace Game
{
    class Chess
    {
    private:
        Window* m_window;
        ResourceManager* m_resource_manager;

        Color m_turn;
        Board* m_board;
        Piece* m_selected;
        std::vector<Move> m_valid_moves;
        std::vector<std::string> m_history;
        
        bool m_prev_mouse_pressed;

    public:
        Chess();
        ~Chess();

        bool init();
        void run();

    private:
        void render() const;

        Vec2i moused_square() const;
        bool check_click();
        void select_piece(Piece* pice);
        std::string create_state_hash();

        // Declare outside of class instead?
        friend void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id,
            GLenum severity, GLsizei length, const GLchar* message, const void* user_param);
    };
}
