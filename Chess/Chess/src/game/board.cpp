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
            Bishop* bishop = new Bishop(color, this);
            add_piece(bishop, Vec2i(x, start));
        }

        // Knights
        for (int x = 1; x <= 6; x += 5)
        {
            Knight* knight = new Knight(color, this);
            add_piece(knight, Vec2i(x, start));
        }

        // Rooks
        for (int x = 0; x <= 7; x += 7)
        {
            Rook* rook = new Rook(color, this);
            add_piece(rook, Vec2i(x, start));
        }

        // Queen
        Queen* queen = new Queen(color, this);
        add_piece(queen, Vec2i(3, start));


        // King
        King* king = new King(color, this);
        add_piece(king, Vec2i(4, start));

        if (color == Color::White)
            m_white_king = king;
        if (color == Color::White)
            m_black_king = king;

        // Pawns
        for (int x = 0; x < 8; x++)
        {
            Pawn* pawn = new Pawn(color, this);
            add_piece(pawn, Vec2i(x, start + dir));
        }
    }

    void Board::add_piece(Piece* piece, const Vec2i& pos)
    {
        m_pieces.push_back(piece);
        m_board[pos.y][pos.x] = piece;
        m_group->add(piece->get_sprite());
    }

    Piece* Board::get_piece(const Vec2i& pos) const
    {
        if (!in_bound(pos)) return nullptr;
        return m_board[pos.y][pos.x];
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
    
    bool Board::is_threatened(const Vec2i& pos) const
    {
        Piece* piece = get_piece(pos);
        if (!piece)
            return false;

        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                Vec2i other_pos = Vec2i(x, y); 
                Piece* other_piece = get_piece(other_pos);
                if (other_piece && piece->get_color() != other_piece->get_color())
                {
                    for (const Move& move : other_piece->moves(other_pos))
                    {
                        if (move.new_pos == pos)
                            return true;
                    }
                }
            }
        }

        return false;
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

    std::unordered_map<Vec2i, std::vector<Move>> Board::valid_moves(Color color)
    {
        std::unordered_map<Vec2i, std::vector<Move>> valid_moves_map;
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
                        valid_moves_map[pos] = valid_moves;
                    }
                }
            }

        return valid_moves_map;
    }
    
    Vec2i Board::get_pos(const Piece* piece) const
    {
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                Vec2i pos = Vec2i(x, y);
                if (get_piece(pos) == piece) return pos;
            }
        }

        return Vec2i(-1, -1);
    }
    
    bool Board::is_valid_move(const Vec2i& pos, const Move& move)
    {
        Piece* piece = get_piece(pos);
        if (!piece)
            return false;
        
        Piece* captured = get_piece(pos);

        if (captured) 
            set_pos(move.captured_pos, nullptr);

        set_pos(pos, nullptr);
        set_pos(move.new_pos, piece);

        King* king;
        if (piece->get_color() == Color::White)
            king = m_black_king;
        else 
            king = m_white_king;
        
        bool valid = !is_threatened(get_pos(king));

        // Undo move
        set_pos(pos, piece);
        set_pos(move.new_pos, nullptr);

        if (captured)
            set_pos(move.captured_pos, captured);

        return valid;
    }
}