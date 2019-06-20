#pragma once

#include <string>
#include <map>
#include <nlohmann/json.hpp>

#include "BlockPartFace.h"

class BlockPart
{
public:
	std::map<std::string, BlockPartFace> faces;
};

void from_json(const nlohmann::json& json, BlockPart& bp);