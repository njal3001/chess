#include "chess/game/board.h"

namespace Game
{
    Board::Board(Vec2 pos, Vec2 size, TextureArray* texture_array)
        : m_pos(pos), m_texture_array(texture_array), m_sprite(nullptr)
    {
        m_group = new Group(Mat4x4::create_translation(
            Vec3(pos.x, pos.y, 0)) * Mat4x4::create_scale(Vec3(size.x, size.y, 1)));
        auto texture = m_texture_array->add("res/textures/Board.png");
        m_sprite = new Sprite(Vec2(), Vec2(64, 64), texture);
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

        // Bishops
        for (int x = 2; x <= 5; x += 3)
        {
            Bishop* bishop = new Bishop(Vec2i(x, start), color, this);
            m_board[start][x] = bishop;
            m_group->add(bishop->get_sprite());
        }

        // Knights
        for (int x = 1; x <= 6; x += 5)
        {
            Knight* knight = new Knight(Vec2i(x, start), color, this);
            m_board[start][x] = knight;
            m_group->add(knight->get_sprite());
        }

        // Rooks
        for (int x = 0; x <= 7; x += 7)
        {
            Rook* rook = new Rook(Vec2i(x, start), color, this);
            m_board[start][x] = rook;
            m_group->add(rook->get_sprite());
        }

        // Queen
        Queen* queen = new Queen(Vec2i(3, start), color, this);
        m_board[start][3] = queen;
        m_group->add(queen->get_sprite());


        // King
        King* king = new King(Vec2i(4, start), color, this);
        m_board[start][4] = king;
        m_group->add(king->get_sprite());

        if (color == Piece::white)
            m_white_king = king;
        if (color == Piece::white)
            m_black_king = king;

        // Pawns
        for (int x = 0; x < 8; x++)
        {
            Pawn* pawn = new Pawn(Vec2i(x, start + dir), color, this);
            m_board[start + dir][x] = pawn;
            m_group->add(pawn->get_sprite());
        }
    }

    const Piece* Board::get_piece(Vec2i pos) const
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


    bool Board::in_bound(Vec2i pos) const
    {
        return pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8;
    }

    bool Board::has_color(Vec2i pos, Piece::Color color) const
    {
        if (!in_bound(pos)) return false;

        Piece* piece = m_board[pos.y][pos.x];
        return piece && piece->get_color() == color;
    }

    bool Board::can_move_from(Vec2i pos) const
    {
        return true;
    }

    bool Board::valid_move(Vec2i old_pos, Vec2i new_pos) const
    {
        return true;
    }
    
    bool Board::is_threatened(Vec2i pos, Piece::Color color) const
    {
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                std::cout << Vec2i(x, y) << std::endl;
                Piece* piece = m_board[y][x];
                if (piece && (piece->get_color() != color))
                {
                    auto moves = piece->valid_moves();
                    if (std::find(moves.begin(), moves.end(), pos) != moves.end())
                        return true;
                }
            }
        }

        return false;
    }

    bool Board::is_vacant(Vec2i pos) const
    {
        return in_bound(pos) && !m_board[pos.y][pos.x];
    }

    bool Board::move_piece(Vec2i old_pos, Vec2i new_pos)
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