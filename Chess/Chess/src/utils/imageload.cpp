#include "chess/utils/imageload.h"
#include <iostream>

namespace Game
{
    FIBITMAP* Utils::load_image(const char* filename)
    {
        FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
        FIBITMAP* dib = nullptr;
        fif = FreeImage_GetFileType(filename, 0);
        if (fif == FIF_UNKNOWN)
            fif = FreeImage_GetFIFFromFilename(filename);
        if (fif == FIF_UNKNOWN)
            return nullptr;

        if (FreeImage_FIFSupportsReading(fif))
            dib = FreeImage_Load(fif, filename);
        if (!dib)
            return nullptr;

        return dib;
    }
}
