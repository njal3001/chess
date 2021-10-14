#include "chess/game/board.h"

namespace Game
{
    Board::Board(const Vec2& pos, const Vec2& size, TextureArray* texture_array)
        :m_pos(pos), m_texture_array(texture_array), m_sprite(nullptr)
    {
        m_group = new Group(Mat4x4::create_translation(
            Vec3(pos.x, pos.y, 0)) * Mat4x4::create_scale(Vec3(size.x, size.y, 1)));
        auto texture = m_texture_array->add("res/textures/Board.png");
        m_sprite = new Sprite(Vec2(), Vec2(64, 64), texture);
        m_group->add(m_sprite);


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
        if (color == Color::White)
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
        m_pieces.push_back(piece);
        const Vec2i& pos = piece->get_pos();
        m_board[pos.y][pos.x] = piece;
        m_group->add(piece->get_sprite());
    }

    Piece* Board::get_piece(const Vec2i& pos) const
    {
        return m_board[pos.y][pos.x];
    }

    TextureArray* Board::get_texture_array() const
    {
        return m_texture_array;
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
    
    bool Board::is_threatened(Piece* piece) const
    {
        for (Piece* p: m_pieces)
        {
                if (!p->is_dead() && piece->get_color() != p->get_color())
                {
                    for (const auto& move : piece->valid_moves())
                    {
                        if (move.new_pos == piece->get_pos())
                            return true;
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

    bool Board::move_piece(Piece* piece, const Move& move)
    {
        if (!piece)
            return false;
        
        if (move.captured)
            set_pos(move.captured->get_pos(), nullptr);

        set_pos(piece->get_pos(), nullptr);
        set_pos(move.new_pos, piece);

        King* king;
        if (piece->get_color() == Color::White)
            king = m_black_king;
        else 
            king = m_white_king;
        
        if (is_threatened(king))
        {
            std::cout << "Illegal move!" << std::endl;
            // Undo move
            set_pos(piece->get_pos(), piece);
            set_pos(move.new_pos, nullptr);

            if (move.captured)
                set_pos(move.captured->get_pos(), move.captured);

            return false;
        }
        else 
        {
            piece->move(move.new_pos);
            if (move.captured)
                move.captured->kill();

            pass_turn(piece);

            return true;
        }
    }

    void Board::pass_turn(Piece* moved_piece)
    {
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                Piece* curr_piece = m_board[y][x];
                if (curr_piece && curr_piece != moved_piece && curr_piece->get_color() == moved_piece->get_color())
                    curr_piece->pass();
            }
        }
    }
}