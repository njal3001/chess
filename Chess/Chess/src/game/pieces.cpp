#include "chess/game/pieces.h"
#include "chess/game/piece.h"
#include "chess/game/board.h"

namespace Game
{

    King::King(const Vec2i& start_pos, Color color, Board* board)
        : Piece(start_pos, color, board, "res/textures/King.png")
    {}

    std::vector<Move> King::moves(const Vec2i& pos) const
    {
        return get_spot_moves(pos, {Vec2i(1, 0), Vec2i(1, 1), Vec2i(1, -1), 
            Vec2i(0, 1), Vec2i(0, -1), Vec2i(-1, 1), Vec2i(-1, -1), Vec2i(-1, 0)}, false, false);
    }

    bool King::check_castle(const Vec2i& pos, const Vec2i& new_pos) const
    {
        if (has_moved())
            return false;

        int dir = Calc::sgn(new_pos.x - pos.x);
        if (new_pos != pos + Vec2i(2 * dir, 0))
            return false;
        
        Vec2i rook_pos = Vec2i(dir == 1 ? 7 : 0, pos.y);
        Piece* rook = m_board->get_piece(rook_pos);
        if (!rook || rook->has_moved())
            return false;
        
        std::vector<Vec2i> check_positions;
        int x = pos.x + dir;
        while (x > 1 && x < 7)
        {
            Vec2i check_pos = Vec2i(x, pos.y);
            if (!m_board->is_vacant(check_pos))
                return false;

            check_positions.push_back(check_pos);
            x += dir;
        }

        return !m_board->is_threatened(check_positions, m_color);
    }

    Pawn::Pawn(const Vec2i& start_pos, Color color, Board* board)
        : Piece(start_pos, color, board, "res/textures/Pawn.png")
    {}


    bool Pawn::check_en_passant() const
    {
        Vec2i curr_pos = m_board->get_pos(this, 0);
        Vec2i prev_pos = m_board->get_pos(this, 1);

        if (!m_board->in_bound(prev_pos) || !m_board->in_bound(curr_pos))
            return false;

        return abs(curr_pos.y - prev_pos.y) == 2;
    }

    std::vector<Move> Pawn::moves(const Vec2i& pos) const
    {
        std::vector<Vec2i> empty_offset = {Vec2i(0, 1 * m_forward)};
        if (!has_moved())
            empty_offset.push_back(Vec2i(0, 2 * m_forward));
        
        std::vector<Move> moves = get_spot_moves(pos, empty_offset, true, false);

        std::vector<Move> threat_moves = get_spot_moves(pos, {Vec2i(1, m_forward), Vec2i(-1, m_forward)}, false, true);

        for (const auto& move: threat_moves)
            moves.push_back(move);

        // En passant
        Vec2i right_pos = Vec2i(pos.x + 1, pos.y);
        Vec2i left_pos = Vec2i(pos.x - 1, pos.y);
        Piece* right_piece = m_board->get_piece(right_pos);
        Piece* left_piece = m_board->get_piece(left_pos);

        if (right_piece && right_piece->get_color() != m_color && right_piece->check_en_passant())
            moves.push_back({right_pos + Vec2i(0, m_forward), right_pos});

        if (left_piece && left_piece->get_color() != m_color && left_piece->check_en_passant())
            moves.push_back({left_pos + Vec2i(0, m_forward), left_pos});

        return moves;
    }


    Bishop::Bishop(const Vec2i& start_pos, Color color, Board* board)
        : Piece(start_pos, color, board, "res/textures/Bishop.png")
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

    Knight::Knight(const Vec2i& start_pos, Color color, Board* board)
        : Piece(start_pos, color, board, "res/textures/Horse.png")
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


    Rook::Rook(const Vec2i& start_pos, Color color, Board* board)
        : Piece(start_pos, color, board, "res/textures/Tower.png")
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


    Queen::Queen(const Vec2i& start_pos, Color color, Board* board)
        : Piece(start_pos, color, board, "res/textures/Queen.png")
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