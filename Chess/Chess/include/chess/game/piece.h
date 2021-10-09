#pragma once
#include "chess/maths/maths.h"
#include "chess/graphics/sprite.h"

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
        Vec2i m_pos;
        Color m_color;
        const Board* m_board;

    private:
        Sprite* m_sprite;

    protected:
        Piece(const Vec2i& pos, Color color, const Board* board, const std::string& sprite_path);
    
    public:
        virtual std::vector<Vec2i> valid_moves() const = 0;

        void render(Vec2i pos, BatchRenderer2D* renderer);

        void set_pos(const Vec2i& pos);
        const Vec2i&  get_pos() const;

        Color get_color() const;
        Sprite* get_sprite() const;
    };
}