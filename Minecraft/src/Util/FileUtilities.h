#pragma once

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

class FileUtilities
{
public:
	static std::string GetContentsAsString(const std::string& file);

	template <typename T>
	static T GetContentsAsJson(const std::string& file)
	{
		std::ifstream ifs(file);
		auto raw = nlohmann::json::parse(ifs);
		ifs.close();

		return raw.get<T>();
	}
};