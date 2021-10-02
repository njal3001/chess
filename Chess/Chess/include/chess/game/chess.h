#pragma once
#include "chess/graphics/window.h"
#include "chess/graphics/fontatlas.h"

namespace Chess
{
    namespace Game
    {
        class Chess
        {
        private:
            Graphics::Window* m_window;
            Graphics::FontAtlas* m_font_atlas;

        public:
            Chess();
            ~Chess();

            bool init();
            void run();

        private:
            // Declare outside of class instead?
            friend void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id,
                GLenum severity, GLsizei length, const GLchar* message, const void* user_param);
        };
    }
}
