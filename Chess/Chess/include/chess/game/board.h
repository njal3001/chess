#pragma once
#include "pieces.h"
#include "chess/graphics/sprite.h"
#include "chess/graphics/group.h"

namespace Game 
{
    class Board 
    {
    private:
        Vec2 m_pos;
        Piece* m_board[8][8];
        TextureArray* m_texture_array;
        Sprite* m_sprite;
        Group* m_group;
        King* m_white_king;
        King* m_black_king;
    
    public:
        Board(Vec2 pos, Vec2 size, TextureArray* texture_array);
        ~Board();

        bool in_bound(Vec2i pos) const;
        bool has_color(Vec2i pos, Piece::Color color) const;
        bool can_move_from(Vec2i pos) const;
        bool valid_move(Vec2i old_pos, Vec2i new_pos) const;
        bool is_vacant(Vec2i pos) const;
        bool is_threatened(Vec2i pos, Piece::Color color) const;

        bool move_piece(Vec2i old_pos, Vec2i new_pos);

        const Piece* get_piece(Vec2i pos) const;
        TextureArray* get_texture_array() const;
        Group* get_group() const;
    
    private:
        void create_pieces(Piece::Color color);
    };
}