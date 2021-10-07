#include "chess/game/pieces.h"
#include "chess/game/piece.h"
#include "chess/game/board.h"

namespace Chess
{
    namespace Game
    {

        std::vector<Maths::Vec2i> get_moves(const Board* board, const Piece* piece, 
            const std::vector<Maths::Vec2i>& step_dirs)
        {
            std::vector<Maths::Vec2i> moves;

            for (auto step : step_dirs) 
            {
                int step_count = 1;
                while (true)
                {
                    Maths::Vec2i new_pos = piece->get_pos() + step * step_count;
                    if (board->is_vacant(new_pos) || board->has_color(new_pos, Piece::opposite(piece->get_color())))
                        moves.push_back(new_pos);
                    else
                        break;
                    
                    step_count++;
                }
            }

            return moves;
        }

        King::King(Maths::Vec2i pos, Piece::Color color, Board* board)
            : Piece(pos, color, board, "res/textures/King.png")
        {}

        std::vector<Maths::Vec2i> King::valid_moves() const
        {
            std::vector<Maths::Vec2i> moves;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    auto new_pos = Maths::Vec2i(m_pos.x + x, m_pos.y + y);
                    if (new_pos == m_pos) continue;

                    if (m_board->in_bound(new_pos) && !m_board->has_color(new_pos, m_color))
                        moves.push_back(new_pos);
                }
            }

            return moves;
        }

        Pawn::Pawn(Maths::Vec2i pos, Piece::Color color, Board* board)
            : Piece(pos, color, board, "res/textures/Pawn.png")
        {}

        // TODO: Add support for en passant
        std::vector<Maths::Vec2i> Pawn::valid_moves() const
        {
            std::vector<Maths::Vec2i> moves;
            int dir = m_color == Color::white ? -1 : 1;
            int max_dist = (m_pos.y == (m_color == Color::white ? 6 : 1)) ? 2 : 1;

            for (int dist = 1; dist <= max_dist; dist++) 
            {
                auto new_pos = Maths::Vec2i(m_pos.x, m_pos.y + dir * dist);
                if (m_board->is_vacant(new_pos))
                    moves.push_back(new_pos);
            }

            for (int x = -1; x <= 1; x += 2)
            {
                auto new_pos = Maths::Vec2i(m_pos.x + x, m_pos.y + dir);
                if (m_board->has_color(new_pos, opposite(m_color)))
                    moves.push_back(new_pos);
            }

            return moves;
        }


        Bishop::Bishop(Maths::Vec2i pos, Piece::Color color, Board* board)
            : Piece(pos, color, board, "res/textures/Bishop.png")
        {}

        std::vector<Maths::Vec2i> Bishop::valid_moves() const
        {
            std::vector<Maths::Vec2i> step_dirs = 
            {
                Maths::Vec2i(1, 1),
                Maths::Vec2i(1, -1),
                Maths::Vec2i(-1, 1),
                Maths::Vec2i(-1, -1),
            };
            
            return get_moves(m_board, this, step_dirs);
        }
    
        Knight::Knight(Maths::Vec2i pos, Piece::Color color, Board* board)
            : Piece(pos, color, board, "res/textures/Horse.png")
        {}

        std::vector<Maths::Vec2i> Knight::valid_moves() const
        {
            std::vector<Maths::Vec2i> moves;

            for (int x = -2; x <= 2; x++)
            {
                if (x == 0) continue;

                for (int y = -2; y <= 2; y++)
                {
                    if (y == 0) continue;

                    Maths::Vec2i new_pos = Maths::Vec2i(m_pos.x + x, m_pos.y + y);
                    if (m_board->is_vacant(new_pos) || m_board->has_color(new_pos, opposite(m_color)))
                        moves.push_back(new_pos);
                }
            }

            return moves;
        }


        Rook::Rook(Maths::Vec2i pos, Piece::Color color, Board* board)
            : Piece(pos, color, board, "res/textures/Tower.png")
        {}

        std::vector<Maths::Vec2i> Rook::valid_moves() const
        {
            std::vector<Maths::Vec2i> step_dirs = 
            {
                Maths::Vec2i(1, 0),
                Maths::Vec2i(-1, 0),
                Maths::Vec2i(0, 1),
                Maths::Vec2i(0, -1),
            };

            return get_moves(m_board, this, step_dirs);
        }


        Queen::Queen(Maths::Vec2i pos, Piece::Color color, Board* board)
            : Piece(pos, color, board, "res/textures/Queen.png")
        {}

        std::vector<Maths::Vec2i> Queen::valid_moves() const
        {
            std::vector<Maths::Vec2i> step_dirs = 
            {
                Maths::Vec2i(1, 0),
                Maths::Vec2i(-1, 0),
                Maths::Vec2i(0, 1),
                Maths::Vec2i(0, -1),
                Maths::Vec2i(1, 1),
                Maths::Vec2i(1, -1),
                Maths::Vec2i(-1, 1),
                Maths::Vec2i(-1, -1),
            };

            return get_moves(m_board, this, step_dirs);
        }
    }
}