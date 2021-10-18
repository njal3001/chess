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

    Piece::Piece(const Vec2i& start_pos, Color color, const Board* board, const std::string& sprite_path)
        :  m_start_pos(start_pos), m_color(color), m_board(board)
    {
        TextureArray::Element texture = board->get_resource_manager()->get_sprite_array()->add(sprite_path);
        m_sprite = new Sprite(Vec2(), Vec2(8, 8),
            color == Color::White ? Vec4(1, 1, 1, 1) : Vec4(0, 0, 0, 1),  texture);

        m_id = id++;
        m_forward = color == Color::White ? -1 : 1;
    }

    bool Piece::check_en_passant() const
    {
        return false;
    }

    bool Piece::check_castle(const Vec2i& pos, const Vec2i& new_pos) const
    {
        return false;
    }


   bool Piece::check_promote(const Vec2i& pos) const
   {
       return false;
   }
    
    Vec2i Piece::get_start_pos() const
    {
        return m_start_pos;
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

    std::vector<Move> Piece::get_beam_moves(const Vec2i& pos, const std::vector<Vec2i>& step_dirs) const
    {
        std::vector<Move> moves;

        for (auto step : step_dirs) 
        {
            int step_count = 1;
            while (true)
            {
                Vec2i new_pos = pos + step * step_count;
                if (m_board->is_vacant(new_pos))
                {
                    Move move = {new_pos, new_pos};
                    moves.push_back(move);
                }
                else if (m_board->has_color(new_pos, opposite(m_color)))
                {
                    Move move = {new_pos, new_pos};
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

    std::vector<Move> Piece::get_spot_moves(const Vec2i& pos, const std::vector<Vec2i>& offsets,
         bool empty_only, bool threat_only) const
    {
        std::vector<Move> moves;

        for (auto offset: offsets)
        {
            auto new_pos = pos + offset;

            if (m_board->is_vacant(new_pos) && !threat_only)
            {
                moves.push_back({new_pos, new_pos});
            }
            else if (m_board->has_color(new_pos, opposite(m_color)) && !empty_only)
            {
                Move move = {new_pos, new_pos};
                moves.push_back(move);
            }
        }

        return moves;
    }
        
    bool Piece::has_moved() const
    {
        for (const std::string& hash : m_board->get_history()) 
        {
            if (hash[m_start_pos.y * 8 + m_start_pos.x] != m_id)
                return true;
        }

        return false;
    }
}