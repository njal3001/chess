#include "chess/utils/file.h";

namespace Chess
{
	// Source: https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring

	std::string Utils::read_file(const char* filepath)
	{
        std::ifstream in(filepath);

        in.seekg(0, std::ios::end);
        size_t size = in.tellg();
        std::string contents(size, ' ');

        in.seekg(0);
        in.read(&contents[0], size);
        in.close();

        return contents;
	}
}
