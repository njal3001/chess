#include "chess/game/piece.h"
#include "chess/graphics/batchrenderer2d.h"
#include "chess/game/board.h"

namespace Game
{
    Piece::Color Piece::opposite(Piece::Color color)
    {
        switch (color)
        {
            case Piece::Color::white : return Piece::Color::black; break;
            case Piece::Color::black : return Piece::Color::white; break;
        }
    }

    Piece::Piece(const Vec2i& pos, Piece::Color color, const Board* board, const std::string& sprite_path)
        :  m_color(color), m_board(board)
    {
        TextureArray::Element texture = board->get_texture_array()->add(sprite_path);
        m_sprite = new Sprite(Vec2(), Vec2(8, 8),
            color == Piece::Color::white ? Vec4(1, 1, 1, 1) : Vec4(0, 0, 0, 1),  texture);

        set_pos(pos);
    }

    void Piece::set_pos(const Vec2i& pos)
    {
        m_pos = pos;
        m_sprite->position = Vec3(pos.x * 8, 56 - pos.y * 8, 0);
    }

    const Vec2i& Piece::get_pos() const
    {
        return m_pos;
    }

    Piece::Color Piece::get_color() const
    {
        return m_color;
    }

    Sprite* Piece::get_sprite() const
    {
        return m_sprite;
    }

    void Piece::render(Vec2i pos, BatchRenderer2D* renderer)
    {
        m_sprite->position = Vec3(pos.x, pos.y, 0);
        m_sprite->submit(renderer);
    }
}