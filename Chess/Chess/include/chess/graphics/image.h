#include "chess/utils/imageload.h"
#include <string>

namespace Chess
{
    namespace Graphics
    {
        class Image
        {
        private:
            FIBITMAP* m_dib;

        public:
            Image(const std::string& filename);
            ~Image();

            const BYTE* get_bits() const;
            const int get_width() const;
            const int get_height() const;
        };
    }
}
