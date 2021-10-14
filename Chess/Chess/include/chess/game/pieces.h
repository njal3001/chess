#pragma once
#include "piece.h"

namespace Game
{

    class King : public Piece
    {
    public:
        King(const Vec2i& pos, Color color, Board* board);
        std::vector<Move> valid_moves() const override;
    };

    class Rook : public Piece
    {
    public:
        Rook(const Vec2i& pos, Color color, Board* board);
        std::vector<Move> valid_moves() const override;
    };
    
    class Bishop : public Piece
    {
    public:
        Bishop(const Vec2i& pos, Color color, Board* board);
        std::vector<Move> valid_moves() const override;
    };

    class Queen : public Piece
    {
    public:
        Queen(const Vec2i& pos, Color color, Board* board);
        std::vector<Move> valid_moves() const override;
    };

    class Knight : public Piece
    {
    public:
        Knight(const Vec2i& pos, Color color, Board* board);
        std::vector<Move> valid_moves() const override;
    };
    
    class Pawn : public Piece
    {
    public:
        Pawn(const Vec2i& pos, Color color, Board* board);
        std::vector<Move> valid_moves() const override;
        bool check_en_passant() const override;
    };
}