#pragma once
#include "chess/maths/maths.h"
#include "chess/graphics/sprite.h"

namespace Game
{
    class Board;
    class Piece;

    enum class Color
    {
        White = 0,
        Black = 1
    };

    Color opposite(Color color);

    struct Move
    {
        Vec2i new_pos;
        Vec2i captured_pos;
    };

    class Piece
    {
    protected:
        char m_id;
        Color m_color;
        const Board* m_board;
        int m_forward;

    private:
        static char id;

        Sprite* m_sprite;

    protected:
        Piece(Color color, const Board* board, const std::string& sprite_path);
        std::vector<Move> get_beam_moves(const Vec2i& pos, const std::vector<Vec2i>& step_dirs) const;
        std::vector<Move> get_spot_moves(const Vec2i& pos, const std::vector<Vec2i>& offsets, bool empty_only, bool threat_only) const;
    
    public:
        virtual std::vector<Move> moves(const Vec2i& pos) const = 0;
        virtual bool check_en_passant() const;
        virtual bool check_castle(const Vec2i& new_pos) const;
        bool has_moved() const;

        Color get_color() const;
        Sprite* get_sprite() const;
        char get_id() const;
    };
}