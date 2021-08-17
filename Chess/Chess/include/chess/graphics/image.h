#include "chess/utils/imageload.h"

namespace Chess
{
    namespace Graphics
    {
        class Image
        {
        private:
            FIBITMAP* m_dib;

        public:
            Image(const char* filename);
            ~Image();

            const BYTE* get_bits() const;
            const int get_width() const;
            const int get_height() const;
        };
    }
}
