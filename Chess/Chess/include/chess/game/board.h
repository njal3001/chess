#pragma once
#include "pieces.h"
#include "chess/graphics/sprite.h"
#include "chess/graphics/group.h"

namespace Chess 
{
    namespace Game 
    {
        class Board 
        {
        private:
            Maths::Vec2 m_pos;
            Piece* m_board[8][8];
            Graphics::TextureArray* m_texture_array;
            Graphics::Sprite* m_sprite;
            Graphics::Group* m_group;
            King* m_white_king;
            King* m_black_king;
        
        public:
            Board(Maths::Vec2 pos, Maths::Vec2 size, Graphics::TextureArray* texture_array);
            ~Board();

            bool in_bound(Maths::Vec2i pos) const;
            bool has_color(Maths::Vec2i pos, Piece::Color color) const;
            bool can_move_from(Maths::Vec2i pos) const;
            bool valid_move(Maths::Vec2i old_pos, Maths::Vec2i new_pos) const;
            bool is_vacant(Maths::Vec2i pos) const;
            bool is_threatened(Maths::Vec2i pos, Piece::Color color) const;

            bool move_piece(Maths::Vec2i old_pos, Maths::Vec2i new_pos);

            const Piece* get_piece(Maths::Vec2i pos) const;
            Graphics::TextureArray* get_texture_array() const;
            Graphics::Group* get_group() const;
        
        private:
            void create_pieces(Piece::Color color);
        };

    }
}