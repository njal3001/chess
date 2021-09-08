#include "chess/maths/maths.h"

namespace Chess
{
    namespace Graphics
    {
        class TextureAtlas
        {
        private:
            const Maths::Vec2 m_size;

        public:
            TextureAtlas(const Maths::Vec2& size);
            ~TextureAtlas();

            init();
        };
    }
}
