#pragma once

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

class FileUtil
{
public:
	static bool getContentsAsString(const std::string& file, std::string& contents);

	template <typename  T>
	static bool getContentsAsJson(const std::string& file, T& contents)
	{
		std::ifstream ifs(file);
		if (!ifs)
			return false;

		auto raw = nlohmann::json::parse(ifs);

		contents = raw.get<T>();

		return true;
	}
};