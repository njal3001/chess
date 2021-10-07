#pragma once
#include "piece.h"

namespace Chess
{
    namespace Game
    {
        std::vector<Maths::Vec2i> get_moves(const Board* board, const Piece* piece, 
            const std::vector<Maths::Vec2i>& step_dirs);

        class King : public Piece
        {
        public:
            King(Maths::Vec2i pos, Piece::Color color, Board* board);
            std::vector<Maths::Vec2i> valid_moves() const override;
        };

        class Rook : public Piece
        {
        public:
            Rook(Maths::Vec2i pos, Piece::Color color, Board* board);
            std::vector<Maths::Vec2i> valid_moves() const override;
        };
        
        class Bishop : public Piece
        {
        public:
            Bishop(Maths::Vec2i pos, Piece::Color color, Board* board);
            std::vector<Maths::Vec2i> valid_moves() const override;
        };

        class Queen : public Piece
        {
        public:
            Queen(Maths::Vec2i pos, Piece::Color color, Board* board);
            std::vector<Maths::Vec2i> valid_moves() const override;
        };

        class Knight : public Piece
        {
        public:
            Knight(Maths::Vec2i pos, Piece::Color color, Board* board);
            std::vector<Maths::Vec2i> valid_moves() const override;
        };
        
        class Pawn : public Piece
        {
        public:
            Pawn(Maths::Vec2i pos, Piece::Color color, Board* board);
            std::vector<Maths::Vec2i> valid_moves() const override;
        };
    }
}