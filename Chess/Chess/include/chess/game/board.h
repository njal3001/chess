#pragma once
#include "pieces.h"
#include "chess/graphics/sprite.h"
#include "chess/graphics/resourcemanager.h"
#include "chess/graphics/group.h"

namespace Game 
{
    class Board 
    {
    private:
        Vec2 m_pos;
        std::vector<Piece*> m_pieces;
        std::vector<std::string> m_history;
        Piece* m_board[8][8];
        ResourceManager* m_resource_manager;
        Sprite* m_sprite;
        Group* m_group;
        King* m_white_king;
        King* m_black_king;
    
    public:
        Board(const Vec2& pos, const Vec2& size, ResourceManager* resource_manager);
        ~Board();

        bool in_bound(const Vec2i& pos) const;
        bool has_color(const Vec2i& pos, Color color) const;
        bool is_vacant(const Vec2i& pos) const;

        bool move_piece(const Vec2i& pos, const Move& move);
        std::unordered_map<Piece*, std::vector<Move>> valid_moves(Color color);
        void castle(Color color, int dir);

        Piece* get_piece(const Vec2i& pos) const;
        std::unordered_map<Piece*, Vec2i> get_pieces() const;
        Vec2i get_pos(const Piece* piece, int index = 0) const;
        bool is_threatened(const std::vector<Vec2i>& positions, Color color) const;
        bool king_threatened(Color color) const;
        ResourceManager* get_resource_manager() const;
        Group* get_group() const;
        std::string create_state_hash() const;
        void push_history(const std::string& hash);
        const std::vector<std::string>& get_history() const;
    
    private:
        void create_pieces(Color color);
        void add_piece(Piece* piece);
        void set_pos(const Vec2i& pos, Piece* piece);
        const King* get_king(Color color) const;
        bool is_valid_move(const Vec2i& pos, const Move& move);
    };
}