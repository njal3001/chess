#include "chess/game/pieces.h"
#include "chess/game/piece.h"
#include "chess/game/board.h"

namespace Chess
{
    namespace Game
    {
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

                    if (m_board->in_bound(new_pos) && !m_board->has_color(new_pos, m_color) && !m_board->is_threatened(new_pos, m_color))
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
            int max_dist = m_pos.y == (m_color == Color::white ? 1 : 6) ? 2 : 1;

            for (int dist = 1; dist <= max_dist; dist++) 
            {
                auto new_pos = Maths::Vec2i(m_pos.x, m_pos.y + dir * dist);
                if (m_board->in_bound(new_pos) && !m_board->has_color(new_pos, m_color))
                    moves.push_back(new_pos);
            }

            for (int x = -1; x <- 1; x += 2)
            {
                auto new_pos = Maths::Vec2i(m_pos.x + x, m_pos.y + dir);
                if (m_board->in_bound(new_pos)  && m_board->has_color(new_pos, opposite(m_color)))
                    moves.push_back(new_pos);
            }

            return moves;
        }
    }
}