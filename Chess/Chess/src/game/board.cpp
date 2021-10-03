#include "chess/game/board.h"

namespace Chess
{
    namespace Game
    {
        Board::Board(Maths::Vec2 pos, Maths::Vec2 size, Graphics::TextureArray* texture_array)
            : m_pos(pos), m_texture_array(texture_array), m_sprite(nullptr)
        {
            m_group = new Graphics::Group(Maths::Mat4x4::create_translation(
                Maths::Vec3(pos.x, pos.y, 0)) * Maths::Mat4x4::create_scale(Maths::Vec3(size.x, size.y, 1)));
            auto texture = m_texture_array->add("res/textures/Board.png");
            m_sprite = new Graphics::Sprite(Maths::Vec2(), Maths::Vec2(64, 64), texture);
            m_group->add(m_sprite);


            for (int y = 0; y < 8; y++)
                for (int x = 0; x < 8; x++)
                    m_board[y][x] = nullptr;

            create_pieces(Piece::Color::black);
            create_pieces(Piece::Color::white);
        }

        Board::~Board()
        {
            for (int y = 0; y < 8; y++)
            {
                for (int x = 0; x < 8; x++)
                {
                    if (m_board[y][x])
                        delete m_board[y][x];
                }
            }
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
                Pawn* pawn = new Pawn(Maths::Vec2i(x, start + dir), color, this);
                m_board[start + dir][x] = pawn;
                m_group->add(pawn->get_sprite());
            }
        }

        const Piece* Board::get_piece(Maths::Vec2i pos) const
        {
            return m_board[pos.y][pos.x];
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
            if (!in_bound(pos)) return false;

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

        bool Board::is_vacant(Maths::Vec2i pos) const
        {
            return in_bound(pos) && !m_board[pos.y][pos.x];
        }

        bool Board::move_piece(Maths::Vec2i old_pos, Maths::Vec2i new_pos)
        {
            Piece* piece = m_board[old_pos.y][old_pos.x];
            if (!piece)
                return false;

            auto valid_moves = piece->valid_moves();

            if (std::find(valid_moves.begin(), valid_moves.end(), new_pos) != valid_moves.end())
            {

                Piece* old_piece = m_board[new_pos.y][new_pos.x];
                if (old_piece)
                {
                    // TODO: Quick fix, very error prone way of removing pieces
                    old_piece->get_sprite()->hidden = true;
                    delete old_piece;
                }

                m_board[new_pos.y][new_pos.x] = piece;
                piece->set_pos(new_pos);

                m_board[old_pos.y][old_pos.x] = nullptr;

                return true;
            }

            return false;
        }
    }
}