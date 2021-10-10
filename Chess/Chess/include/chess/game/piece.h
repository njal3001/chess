#pragma once
#include "chess/maths/maths.h"
#include "chess/graphics/sprite.h"

namespace Game
{
    class Board;
    class Piece;

    enum class Color
    {
        White,
        Black
    };

    Color opposite(Color color);

    struct Move
    {
        Vec2i new_pos;
        Piece* captured;
    };

    class Piece
    {
    protected:
        bool m_was_moved_prev_turn;
        bool m_has_moved;
        Vec2i m_prev_pos;
        Vec2i m_pos;
        Color m_color;
        const Board* m_board;

    private:
        Sprite* m_sprite;

    protected:
        Piece(const Vec2i& pos, Color color, const Board* board, const std::string& sprite_path);
        std::vector<Move> get_beam_moves(const std::vector<Vec2i>& step_dirs) const;
        std::vector<Move> get_spot_moves(const std::vector<Vec2i>& offsets, bool empty_only, bool threat_only) const;
    
    public:
        virtual std::vector<Move> valid_moves() const = 0;
        virtual bool check_en_passant() const;
        virtual bool check_castle(const Vec2i& new_pos) const;
        bool has_moved() const;

        void render(Vec2i pos, BatchRenderer2D* renderer);

        void pass();
        void move(const Vec2i& new_pos);
        const Vec2i& get_pos() const;

        Color get_color() const;
        Sprite* get_sprite() const;

    private: 
        void set_pos(const Vec2i& pos);
    };
}