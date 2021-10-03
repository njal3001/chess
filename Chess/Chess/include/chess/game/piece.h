#pragma once
#include "chess/maths/maths.h"
#include "chess/graphics/sprite.h"

namespace Chess 
{
    namespace Game
    {
        class Board;

        class Piece
        {
        public:
            enum Color
            {
                white,
                black
            };

            static Color opposite(Color color);

        protected:
            Maths::Vec2i m_pos;
            Color m_color;
            const Board* m_board;

        private:
            Graphics::Sprite* m_sprite;

        protected:
            Piece(const Maths::Vec2i& pos, Color color, const Board* board, const std::string& sprite_path);
        
        public:
            virtual std::vector<Maths::Vec2i> valid_moves() const = 0;

            void render(Maths::Vec2i pos, Graphics::BatchRenderer2D* renderer);

            void set_pos(const Maths::Vec2i& pos);
            const Maths::Vec2i&  get_pos() const;

            Color get_color() const;
            Graphics::Sprite* get_sprite() const;
        };
    }
}