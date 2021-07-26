#pragma once

#include <string>
#include <fstream>
#include <streambuf>

namespace Chess
{
	namespace Utils
	{
		std::string read_file(const char* filepath);
	}
}
