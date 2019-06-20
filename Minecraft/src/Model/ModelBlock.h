#pragma once

#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

#include "BlockPart.h"

class ModelBlock
{
public:
	std::string parentLocation;

	std::vector<BlockPart> elements;
	std::map<std::string, std::string> textures;

	bool is_resolved();
	bool HasParent();

	ModelBlock& GetParent();
private:
	ModelBlock* m_parent;

	
};

void from_json(const nlohmann::json& json, ModelBlock& mb);