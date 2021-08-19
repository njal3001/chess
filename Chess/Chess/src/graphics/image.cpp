#include "chess/graphics/image.h"

namespace Chess
{
    namespace Graphics
    {
        Image::Image(const std::string& filename)
        {
            m_dib = Utils::load_image(filename.c_str());
        }

        Image::~Image()
        {
            FreeImage_Unload(m_dib);
        }

        const BYTE* Image::get_bits() const
        {
            return FreeImage_GetBits(m_dib);
        }

        const int Image::get_width() const
        {
            return FreeImage_GetWidth(m_dib);
        }

        const int Image::get_height() const
        {
            return FreeImage_GetHeight(m_dib);
        }
    }
}
