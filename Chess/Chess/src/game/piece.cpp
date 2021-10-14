#include "chess/game/piece.h"
#include "chess/graphics/batchrenderer2d.h"
#include "chess/game/board.h"

namespace Game
{
    char Piece::id = 1;

    Color opposite(Color color)
    {
        return (Color)(((int)color + 1) % 2);
    }

    Piece::Piece(const Vec2i& pos, Color color, const Board* board, const std::string& sprite_path)
        :  m_color(color), m_board(board), m_prev_pos(pos), m_has_moved(false), m_was_moved_prev_turn(false), m_dead(false)
    {
        TextureArray::Element texture = board->get_resource_manager()->get_sprite_array()->add(sprite_path);
        m_sprite = new Sprite(Vec2(), Vec2(8, 8),
            color == Color::White ? Vec4(1, 1, 1, 1) : Vec4(0, 0, 0, 1),  texture);

        set_pos(pos);

        m_id = id++;
        m_forward = color == Color::White ? -1 : 1;
    }

    bool Piece::check_en_passant() const
    {
        return false;
    }

    bool Piece::check_castle(const Vec2i& new_pos) const
    {
        return false;
    }

    bool Piece::has_moved() const
    {
        return m_has_moved;
    }

    void Piece::pass()
    {
        m_was_moved_prev_turn = false;
    }

    void Piece::move(const Vec2i& new_pos)
    {
        m_has_moved = true;
        m_was_moved_prev_turn = true;
        m_prev_pos = m_pos;
        set_pos(new_pos);
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

    Color Piece::get_color() const
    {
        return m_color;
    }

    Sprite* Piece::get_sprite() const
    {
        return m_sprite;
    }

    char Piece::get_id() const
    {
        return m_id;
    }

    bool Piece::is_dead() const
    {
        return m_dead;
    }

    void Piece::kill() 
    {
        m_dead = true;
        m_sprite->hidden = true;
    }

    std::vector<Move> Piece::get_beam_moves(const std::vector<Vec2i>& step_dirs) const
    {
        std::vector<Move> moves;

        for (auto step : step_dirs) 
        {
            int step_count = 1;
            while (true)
            {
                Vec2i new_pos = m_pos + step * step_count;
                if (m_board->is_vacant(new_pos))
                {
                    Move move = {new_pos, nullptr};
                    moves.push_back(move);
                }
                else if (m_board->has_color(new_pos, opposite(m_color)))
                {
                    Piece* captured = m_board->get_piece(new_pos);
                    Move move = {new_pos, captured};
                    moves.push_back(move);
                    break;
                }
                else
                    break;
                
                step_count++;
            }
        }

        return moves;

    }

    std::vector<Move> Piece::get_spot_moves(const std::vector<Vec2i>& offsets,
         bool empty_only, bool threat_only) const
    {
        std::vector<Move> moves;

        for (auto offset: offsets)
        {
            auto new_pos = m_pos + offset;

            if (m_board->is_vacant(new_pos) && !threat_only)
            {
                moves.push_back({new_pos, nullptr});
            }
            else if (m_board->has_color(new_pos, opposite(m_color)) && !empty_only)
            {
                Move move = {new_pos, m_board->get_piece(new_pos)};
                moves.push_back(move);
            }
        }

        return moves;
    }
}