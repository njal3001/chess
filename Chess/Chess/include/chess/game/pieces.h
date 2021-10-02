#pragma once
#include "piece.h"

namespace Chess
{
    namespace Game
    {
        class King : public Piece
        {
        public:
            King(Piece::Color color, Board* board);
            const std::vector<Maths::Vec2i>& valid_moves(Maths::Vec2i pos) const override;
        };

        class Rook : public Piece
        {
        public:
            Rook(Piece::Color color, Board* board);
            const std::vector<Maths::Vec2i>& valid_moves(Maths::Vec2i pos) const override;
        };
        
        class Bishop : public Piece
        {
        public:
            Bishop(Piece::Color color, Board* board);
            const std::vector<Maths::Vec2i>& valid_moves(Maths::Vec2i pos) const override;
        };

        class Queen : public Piece
        {
        public:
            Queen(Piece::Color color, Board* board);
            const std::vector<Maths::Vec2i>& valid_moves(Maths::Vec2i pos) const override;
        };

        class Knight : public Piece
        {
        public:
            Knight(Piece::Color color, Board* board);
            const std::vector<Maths::Vec2i>& valid_moves(Maths::Vec2i pos) const override;
        };
        
        class Pawn : public Piece
        {
        public:
            Pawn(Piece::Color color, Board* board);
            const std::vector<Maths::Vec2i>& valid_moves(Maths::Vec2i pos) const override;
        };
    }
}