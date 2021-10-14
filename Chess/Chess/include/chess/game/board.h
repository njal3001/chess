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
        std::vector<Piece*> m_pieces;
        std::vector<std::string> m_history;
        Piece* m_board[8][8];
        TextureArray* m_texture_array;
        Sprite* m_sprite;
        Group* m_group;
        King* m_white_king;
        King* m_black_king;
    
    public:
        Board(const Vec2& pos, const Vec2& size, TextureArray* texture_array);
        ~Board();

        bool in_bound(const Vec2i& pos) const;
        bool has_color(const Vec2i& pos, Color color) const;
        bool is_vacant(const Vec2i& pos) const;
        bool is_threatened(Piece* piece) const;

        bool move_piece(Piece* piece, const Move& move);

        Piece* get_piece(const Vec2i& pos) const;
        TextureArray* get_texture_array() const;
        Group* get_group() const;
        std::string get_prev_state(unsigned int index = 0);
    
    private:
        void create_pieces(Color color);
        void pass_turn(Piece* moved_piece);
        void add_piece(Piece* piece);
        void set_pos(const Vec2i& pos, Piece* piece);
        std::string create_state_hash();
    };
}