#include "chess/game/pieces.h"
#include "chess/game/piece.h"
#include "chess/game/board.h"

namespace Game
{

    King::King(Color color, Board* board)
        : Piece(color, board, "res/textures/King.png")
    {}

    std::vector<Move> King::moves(const Vec2i& pos) const
    {
        return get_spot_moves(pos, {Vec2i(1, 0), Vec2i(1, 1), Vec2i(1, -1), 
            Vec2i(0, 1), Vec2i(0, -1), Vec2i(-1, 1), Vec2i(-1, -1), Vec2i(-1, 0)}, false, false);
    }

    Pawn::Pawn(Color color, Board* board)
        : Piece(color, board, "res/textures/Pawn.png")
    {}


    // bool Pawn::check_en_passant(const Vec2i& pos) const
    // {
    //     return m_was_moved_prev_turn && abs(m_pos.y - m_prev_pos[0].y) == 2;
    // }

    std::vector<Move> Pawn::moves(const Vec2i& pos) const
    {
        std::vector<Vec2i> empty_offset = {Vec2i(0, 1 * m_forward)};
        // if (!m_has_moved[0])
        //     empty_offset.push_back(Vec2i(0, 2 * m_forward));
        
        std::vector<Move> moves = get_spot_moves(pos, empty_offset, true, false);

        std::vector<Move> threat_moves = get_spot_moves(pos, {Vec2i(1, m_forward), Vec2i(-1, m_forward)}, false, true);

        for (auto move: threat_moves)
            moves.push_back(move);

        // En passant
        // Vec2i right_pos = Vec2i(m_pos.x + 1, m_pos.y);
        // Vec2i left_pos = Vec2i(m_pos.x - 1, m_pos.y);
        // Piece* right_piece = m_board->get_piece(right_pos);
        // Piece* left_piece = m_board->get_piece(left_pos);

        // if (right_piece && right_piece->get_color() != m_color && right_piece->check_en_passant())
        //     moves.push_back({right_pos + Vec2i(0, m_forward), right_piece});

        // if (left_piece && left_piece->get_color() != m_color && left_piece->check_en_passant())
        //     moves.push_back({left_pos + Vec2i(0, m_forward), left_piece});

        return moves;
    }


    Bishop::Bishop(Color color, Board* board)
        : Piece(color, board, "res/textures/Bishop.png")
    {}

    std::vector<Move> Bishop::moves(const Vec2i& pos) const
    {
        std::vector<Vec2i> step_dirs = 
        {
            Vec2i(1, 1),
            Vec2i(1, -1),
            Vec2i(-1, 1),
            Vec2i(-1, -1),
        };
        
        return get_beam_moves(pos, step_dirs);
    }

    Knight::Knight(Color color, Board* board)
        : Piece(color, board, "res/textures/Horse.png")
    {}

    std::vector<Move> Knight::moves(const Vec2i& pos) const
    {
        std::vector<Vec2i> offsets =
        {
            Vec2i (-1, -2),
            Vec2i (-2, -1),
            Vec2i (-2, 1),
            Vec2i (-1, 2),
            Vec2i (1, 2),
            Vec2i (2, 1),
            Vec2i (2, -1),
            Vec2i (1, -2),
        };

        return get_spot_moves(pos, offsets, false, false);
    }


    Rook::Rook(Color color, Board* board)
        : Piece(color, board, "res/textures/Tower.png")
    {}

    std::vector<Move> Rook::moves(const Vec2i& pos) const
    {
        std::vector<Vec2i> step_dirs = 
        {
            Vec2i(1, 0),
            Vec2i(-1, 0),
            Vec2i(0, 1),
            Vec2i(0, -1),
        };

        return get_beam_moves(pos, step_dirs);
    }


    Queen::Queen(Color color, Board* board)
        : Piece(color, board, "res/textures/Queen.png")
    {}

    std::vector<Move> Queen::moves(const Vec2i& pos) const
    {
        std::vector<Vec2i> step_dirs = 
        {
            Vec2i(1, 0),
            Vec2i(-1, 0),
            Vec2i(0, 1),
            Vec2i(0, -1),
            Vec2i(1, 1),
            Vec2i(1, -1),
            Vec2i(-1, 1),
            Vec2i(-1, -1),
        };

        return get_beam_moves(pos, step_dirs);
    }
}