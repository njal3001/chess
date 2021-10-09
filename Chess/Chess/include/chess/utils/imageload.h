#pragma once
#include <FreeImage.h>
#include <GL/glew.h>

namespace Game
{
    namespace Utils
    {
        FIBITMAP* load_image(const char* filename);
    }
}
