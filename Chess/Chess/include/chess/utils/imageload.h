#pragma once
#include <FreeImage.h>
#include <GL/glew.h>

namespace Chess
{
    namespace Utils
    {
        FIBITMAP* load_image(const char* filename);
    }
}
