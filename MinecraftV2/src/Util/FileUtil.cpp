#include <fstream>
#include <sstream>

#include "FileUtil.h"

bool FileUtil::getContentsAsString(const std::string& file, std::string& contents)
{
	const std::ifstream ifs(file);
	if (!ifs || !ifs.is_open())
	{
		return false;
	}

	std::stringstream stream;
	stream << ifs.rdbuf();

	contents = stream.str();

	return true;
}
