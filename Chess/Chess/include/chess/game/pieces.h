#pragma once
#include "piece.h"

namespace Game
{

    class King : public Piece
    {
    public:
        King(const Vec2i& start_pos, Color color, Board* board);
        std::vector<Move> moves(const Vec2i& pos) const override;
        bool check_castle(const Vec2i& pos, const Vec2i& new_pos) const override;
    };

    class Rook : public Piece
    {
    public:
        Rook(const Vec2i& start_pos, Color color, Board* board);
        std::vector<Move> moves(const Vec2i& pos) const override;
    };
    
    class Bishop : public Piece
    {
    public:
        Bishop(const Vec2i& start_pos, Color color, Board* board);
        std::vector<Move> moves(const Vec2i& pos) const override;
    };

    class Queen : public Piece
    {
    public:
        Queen(const Vec2i& start_pos, Color color, Board* board);
        std::vector<Move> moves(const Vec2i& pos) const override;
    };

    class Knight : public Piece
    {
    public:
        Knight(const Vec2i& start_pos, Color color, Board* board);
        std::vector<Move> moves(const Vec2i& pos) const override;
    };
    
    class Pawn : public Piece
    {
    public:
        Pawn(const Vec2i& start_pos, Color color, Board* board);
        std::vector<Move> moves(const Vec2i& pos) const override;
        bool check_en_passant() const override;
        bool check_promote(const Vec2i& pos) const override;
    };
}