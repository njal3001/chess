#include "chess/game/piece.h"
#include "chess/graphics/batchrenderer2d.h"
#include "chess/game/board.h"

namespace Chess
{
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

        Piece::Piece(Piece::Color color, const Board* board, const std::string& sprite_path)
            : m_color(color), m_board(board)
        {
           Graphics::TextureArray::Element texture = board->get_texture_array()->add(sprite_path);
           m_sprite = new Graphics::Sprite(Maths::Vec2(), Maths::Vec2(8, 8),
             color == Piece::Color::white ? Maths::Vec4(1, 1, 1, 1) : Maths::Vec4(0, 0, 0, 1),  texture);
        }

        Piece::Color Piece::get_color() const
        {
            return m_color;
        }

        Graphics::Sprite* Piece::get_sprite() const
        {
            return m_sprite;
        }

        void Piece::render(Maths::Vec2i pos, Graphics::BatchRenderer2D* renderer)
        {
            m_sprite->position = Maths::Vec3(pos.x, pos.y, 0);
            m_sprite->submit(renderer);
        }
    }
}