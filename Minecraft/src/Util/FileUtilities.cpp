#include <fstream>
#include <sstream>
#include <stdexcept>

#include "FileUtilities.h"

std::string FileUtilities::GetContentsAsString(const std::string& file)
{
	std::ifstream inFile(file);
	if (!inFile.is_open())
	{
		throw std::runtime_error("Unable to open file [ " + file + "]");
	}

	std::stringstream stream;

	stream << inFile.rdbuf();
	return stream.str();
}
