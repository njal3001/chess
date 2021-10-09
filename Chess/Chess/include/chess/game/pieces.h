#pragma once
#include "piece.h"

namespace Game
{
    std::vector<Vec2i> get_moves(const Board* board, const Piece* piece, 
        const std::vector<Vec2i>& step_dirs);

    class King : public Piece
    {
    public:
        King(Vec2i pos, Piece::Color color, Board* board);
        std::vector<Vec2i> valid_moves() const override;
    };

    class Rook : public Piece
    {
    public:
        Rook(Vec2i pos, Piece::Color color, Board* board);
        std::vector<Vec2i> valid_moves() const override;
    };
    
    class Bishop : public Piece
    {
    public:
        Bishop(Vec2i pos, Piece::Color color, Board* board);
        std::vector<Vec2i> valid_moves() const override;
    };

    class Queen : public Piece
    {
    public:
        Queen(Vec2i pos, Piece::Color color, Board* board);
        std::vector<Vec2i> valid_moves() const override;
    };

    class Knight : public Piece
    {
    public:
        Knight(Vec2i pos, Piece::Color color, Board* board);
        std::vector<Vec2i> valid_moves() const override;
    };
    
    class Pawn : public Piece
    {
    public:
        Pawn(Vec2i pos, Piece::Color color, Board* board);
        std::vector<Vec2i> valid_moves() const override;
    };
}