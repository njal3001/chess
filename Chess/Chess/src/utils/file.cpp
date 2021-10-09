#include "chess/utils/file.h"
#include <iostream>
#include <sstream>

namespace Game
{
    // Source: https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
    std::string Utils::read_file(const char* filepath)
    {
        std::ifstream t(filepath);
        std::stringstream buffer;
        buffer << t.rdbuf();
        t.close();
        return buffer.str();
    }
}
