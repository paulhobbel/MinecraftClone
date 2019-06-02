#pragma once

#include <string>
#include <nlohmann/json.hpp>

class FileUtilities
{
public:
	static std::string GetContentsAsString(const std::string& file);
	static nlohmann::json GetContentsAsJson(const std::string& file);
};