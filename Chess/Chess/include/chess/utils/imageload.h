#pragma once
#include <FreeImage.h>
#include <GL/glew.h>

namespace Chess
{
    namespace Utils
    {
        BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height);
    }
}
