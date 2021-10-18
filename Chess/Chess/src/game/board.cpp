#include "chess/game/board.h"

namespace Game
{
    Board::Board(const Vec2& pos, const Vec2& size, ResourceManager* resource_manager)
        :m_pos(pos), m_resource_manager(resource_manager), m_sprite(nullptr)
    {
        m_group = new Group(Mat4x4::create_translation(
            Vec3(pos.x, pos.y, 0)) * Mat4x4::create_scale(Vec3(size.x, size.y, 1)));
        auto texture = m_resource_manager->get_sprite_array()->add("res/textures/Board.png");
        m_sprite = new Sprite(Vec2(), Vec2(64, 64), texture);
        m_group->add(m_sprite);
        m_resource_manager->get_game_layer()->add(m_group);

        for (int y = 0; y < 8; y++)
            for (int x = 0; x < 8; x++)
                m_board[y][x] = nullptr;

        create_pieces(Color::Black);
        create_pieces(Color::White);
    }

    Board::~Board()
    {
        for (auto piece: m_pieces)
            delete piece;
    }

    void Board::create_pieces(Color color)
    {
        int start; 
        int dir = 0;

        if (color == Color::White)
        {
            start = 7;
            dir = -1;
        } else 
        {
            start = 0;
            dir = 1;
        }

        // Bishops
        for (int x = 2; x <= 5; x += 3)
        {
            Bishop* bishop = new Bishop(Vec2i(x, start), color, this);
            add_piece(bishop);
        }

        // Knights
        for (int x = 1; x <= 6; x += 5)
        {
            Knight* knight = new Knight(Vec2i(x, start), color, this);
            add_piece(knight);
        }

        // Rooks
        for (int x = 0; x <= 7; x += 7)
        {
            Rook* rook = new Rook(Vec2i(x, start), color, this);
            add_piece(rook);
        }

        // Queen
        Queen* queen = new Queen(Vec2i(3, start), color, this);
        add_piece(queen);


        // King
        King* king = new King(Vec2i(4, start), color, this);
        add_piece(king);

        if (color == Color::White)
            m_white_king = king;
        if (color == Color::Black)
            m_black_king = king;

        // Pawns
        for (int x = 0; x < 8; x++)
        {
            Pawn* pawn = new Pawn(Vec2i(x, start + dir), color, this);
            add_piece(pawn);
        }
    }

    void Board::add_piece(Piece* piece)
    {
        const Vec2i& pos = piece->get_start_pos();
        m_pieces.push_back(piece);
        m_board[pos.y][pos.x] = piece;
        m_group->add(piece->get_sprite());
    }

    Piece* Board::get_piece(const Vec2i& pos) const
    {
        if (!in_bound(pos)) return nullptr;
        return m_board[pos.y][pos.x];
    }
    
    const King* Board::get_king(Color color) const
    {
        return color == Color::White ? m_white_king : m_black_king;
    }

    ResourceManager* Board::get_resource_manager() const
    {
        return m_resource_manager;
    }

    Group* Board::get_group() const
    {
        return m_group;
    }

    bool Board::in_bound(const Vec2i& pos) const
    {
        return pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8;
    }

    bool Board::has_color(const Vec2i& pos, Color color) const
    {
        if (!in_bound(pos)) return false;

        Piece* piece = m_board[pos.y][pos.x];
        return piece && piece->get_color() == color;
    }
    
    bool Board::is_threatened(const std::vector<Vec2i>& positions, Color color) const
    {
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                Vec2i other_pos = Vec2i(x, y); 
                Piece* other_piece = get_piece(other_pos);
                if (other_piece && color != other_piece->get_color())
                {
                    for (const Move& move : other_piece->moves(other_pos))
                    {
                        if (std::find(positions.begin(), positions.end(), move.captured_pos) != positions.end())
                            return true;
                    }
                }
            }
        }

        return false;
    }
    
    bool Board::king_threatened(Color color) const
    {
        return is_threatened({get_pos(get_king(color))}, color);
    }

    bool Board::is_vacant(const Vec2i& pos) const
    {
        return in_bound(pos) && !m_board[pos.y][pos.x];
    }

    void Board::set_pos(const Vec2i& pos, Piece* piece)
    {
        m_board[pos.y][pos.x] = piece;
    }

    // TODO: Make void instead?
    bool Board::move_piece(const Vec2i& pos, const Move& move)
    {
        Piece* piece = get_piece(pos);
        if (!piece)
            return false;
        
        if (in_bound(move.captured_pos))
            set_pos(move.captured_pos, nullptr);

        set_pos(pos, nullptr);
        set_pos(move.new_pos, piece);

        return true;
    }

    std::unordered_map<Piece*, std::vector<Move>> Board::valid_moves(Color color)
    {
        std::unordered_map<Piece*, std::vector<Move>> valid_moves_map;
        for (int y = 0; y < 8; y++)
            {
                for (int x = 0; x < 8; x++)
                {
                    Vec2i pos = Vec2i(x, y);
                    Piece* piece = get_piece(pos);
                    if (piece && piece->get_color() == color)
                    {
                        std::vector<Move> valid_moves;
                        for (const Move& move : piece->moves(pos))
                        {
                            if (is_valid_move(pos, move))
                                valid_moves.push_back(move);
                        }
                        valid_moves_map[piece] = valid_moves;
                    }
                }
            }

        return valid_moves_map;
    }
    
    Vec2i Board::get_prev_pos(const Piece* piece) const
    {
        if (m_history.size() < 2 || !piece)
            return Vec2i(-1, -1);

        const std::string& hash = m_history[m_history.size() - 2];
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (hash[x + y * 8] == piece->get_id())
                    return Vec2i(x, y);
            }
        }

        return Vec2i(-1, -1);
    }
    

    Vec2i Board::get_pos(const Piece* piece) const
    {
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                Vec2i pos = Vec2i(x, y);
                if (get_piece(pos) == piece)
                    return Vec2i(x, y);
            }
        }

        return Vec2i(-1, -1);
    }

    std::unordered_map<Piece*, Vec2i> Board::get_pieces() const
    {
        std::unordered_map<Piece*, Vec2i> pieces;
        for (Piece* piece : m_pieces)
            pieces[piece] = Vec2i(-1, -1);

        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                Vec2i pos = Vec2i(x, y);
                Piece* piece = get_piece(pos);
                if (piece)
                    pieces[piece] = pos;
            }
        }

        return pieces;
    }
    
    bool Board::is_valid_move(const Vec2i& pos, const Move& move)
    {
        Piece* piece = get_piece(pos);
        if (!piece)
            return false;
        
        Piece* captured = get_piece(move.captured_pos);

        if (captured)
            set_pos(move.captured_pos, nullptr);

        set_pos(pos, nullptr);
        set_pos(move.new_pos, piece);

        bool valid = !king_threatened(piece->get_color());

        // Undo move
        set_pos(pos, piece);
        set_pos(move.new_pos, nullptr);

        if (captured)
            set_pos(move.captured_pos, captured);

        return valid;
    }
    
    void Board::castle(Color color, int dir)
    {
        int y = color == Color::White ? 7 : 0;
        int rook_x = dir == -1 ? 0 : 7;

        Vec2i king_pos = Vec2i(4, y);
        Vec2i rook_pos = Vec2i(rook_x, y);
        Piece* king = get_piece(king_pos);
        Piece* rook = get_piece(rook_pos);

        Vec2i new_king_pos = Vec2i(4 + dir * 2, y);
        set_pos(king_pos, nullptr);
        set_pos(new_king_pos, king);

        set_pos(rook_pos, nullptr);
        set_pos(new_king_pos - Vec2i(dir, 0), rook);
    }

    std::string Board::create_state_hash() const
    {
        std::string hash;
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                Piece* piece = get_piece(Vec2i(x, y));
                if (piece)
                    hash += piece->get_id();
                else
                    hash += (char)0;
            }
        }

        return hash;
    }

    void Board::push_history(const std::string& hash) 
    {

        m_history.push_back(hash);
    }

    const std::vector<std::string>& Board::get_history() const
    {
        return m_history;
    }


    void Board::promote(const Vec2i& pos, Piece* promotion)
    {
        set_pos(pos, nullptr);
        add_piece(promotion);
    }

    void Board::reset_to_prev_state()
    {
        std::string prev_state = m_history[m_history.size() - 1];

        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                char id = prev_state[y * 8 + x];
                Vec2i pos = Vec2i(x, y);

                if (id == (char)0)
                {
                    set_pos(pos, nullptr);
                }
                else
                {
                    for (Piece* piece : m_pieces)
                    {
                        if (piece->get_id() == id)
                        {
                            set_pos(pos, piece);
                        }
                    }
                }
            }
        }
    }
}