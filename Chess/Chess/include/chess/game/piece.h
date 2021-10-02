#include "chess/maths/maths.h"
#include "chess/graphics/sprite.h"

namespace Chess 
{
    namespace Game
    {
        class Board;

        class Piece
        {
        public:
            enum Color
            {
                white,
                black
            };

            static Color opposite(Color color);

        protected:
            Color m_color;
            const Board* m_board;

        private:
            Graphics::Sprite* m_sprite;

        protected:
            Piece(Color color, const Board* board, const std::string& sprite_path);
        
        public:
            virtual const std::vector<Maths::Vec2i>& valid_moves(Maths::Vec2i pos) const = 0;

            void render(Maths::Vec2i pos, Graphics::BatchRenderer2D* renderer);

            Color get_color() const;
            Graphics::Sprite* get_sprite() const;
        };
    }
}