#pragma once
#include "chess/graphics/window.h"
#include "chess/graphics/resourcemanager.h"
#include "board.h"

namespace Chess
{
    namespace Game
    {
        class Chess
        {
        private:
            Graphics::Window* m_window;
            Graphics::ResourceManager* m_resource_manager;

            Piece::Color m_turn;
            Board* m_board;
            const Piece* m_selected;
            std::vector<Maths::Vec2i> m_valid_moves;
            
            bool m_prev_mouse_pressed;

        public:
            Chess();
            ~Chess();

            bool init();
            void run();

        private:
            void render() const;

            Maths::Vec2i moused_square() const;
            bool check_click();
            void select_piece(const Piece* pice);

            // Declare outside of class instead?
            friend void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id,
                GLenum severity, GLsizei length, const GLchar* message, const void* user_param);
        };
    }
}
