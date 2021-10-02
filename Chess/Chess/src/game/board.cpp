#include "chess/game/board.h"

namespace Chess
{
    namespace Game
    {
        Board::Board(Maths::Vec2 pos, Graphics::TextureArray* texture_array)
            : m_pos(pos), m_texture_array(texture_array), m_sprite(nullptr)
        {
            m_group = new Graphics::Group(Maths::Mat4x4::create_translation(Maths::Vec3(pos.x, pos.y, 0)));
            auto texture = m_texture_array->add("res/textures/Board.png");
            m_sprite = new Graphics::Sprite(Maths::Vec2(), Maths::Vec2(64, 64), texture);
            m_group->add(m_sprite);


            for (int y = 0; y < 8; y++)
                for (int x = 0; x < 8; x++)
                    m_board[y][x] = nullptr;

            create_pieces(Piece::Color::white);
            create_pieces(Piece::Color::black);

            for (Piece* piece : m_pieces)
                m_group->add(piece->get_sprite());
        }

        Board::~Board()
        {
            for (auto piece : m_pieces)
                delete piece;
        }

        void Board::create_pieces(Piece::Color color)
        {
            int start; 
            int dir = 0;

            if (color == Piece::Color::white)
            {
                start = 7;
                dir = -1;
            } else 
            {
                start = 0;
                dir = 1;
            }

            // Pawns
            for (int x = 0; x < 8; x++)
            {
                Pawn* pawn = new Pawn(color, this);
                m_board[start + dir][x] = pawn;
                m_pieces.push_back(pawn);
            }
        }

        Graphics::TextureArray* Board::get_texture_array() const
        {
            return m_texture_array;
        }

        Graphics::Group* Board::get_group() const
        {
            return m_group;
        }


        bool Board::in_bound(Maths::Vec2i pos) const
        {
            return pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8;
        }

        bool Board::has_color(Maths::Vec2i pos, Piece::Color color) const
        {
            Piece* piece = m_board[pos.y][pos.x];
            return piece && piece->get_color() == color;
        }

        bool Board::can_move_from(Maths::Vec2i pos) const
        {
            return true;
        }

        bool Board::valid_move(Maths::Vec2i old_pos, Maths::Vec2i new_pos) const
        {
            return true;
        }
        
        bool Board::is_threatened(Maths::Vec2i pos, Piece::Color color) const
        {
            return true;
        }
    }
}