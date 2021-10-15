#pragma once
#include "piece.h"

namespace Game
{

    class King : public Piece
    {
    public:
        King(Color color, Board* board);
        std::vector<Move> moves(const Vec2i& pos) const override;
    };

    class Rook : public Piece
    {
    public:
        Rook(Color color, Board* board);
        std::vector<Move> moves(const Vec2i& pos) const override;
    };
    
    class Bishop : public Piece
    {
    public:
        Bishop(Color color, Board* board);
        std::vector<Move> moves(const Vec2i& pos) const override;
    };

    class Queen : public Piece
    {
    public:
        Queen(Color color, Board* board);
        std::vector<Move> moves(const Vec2i& pos) const override;
    };

    class Knight : public Piece
    {
    public:
        Knight(Color color, Board* board);
        std::vector<Move> moves(const Vec2i& pos) const override;
    };
    
    class Pawn : public Piece
    {
    public:
        Pawn(Color color, Board* board);
        std::vector<Move> moves(const Vec2i& pos) const override;
        bool check_en_passant() const override;
    };
}