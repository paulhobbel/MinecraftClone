#pragma once

#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

#include "BlockPart.h"
#include "../ResourceLoader.h"

class ModelBlock
{
	friend class ResourceLoader;
public:
	std::string id;
	std::string parentLocation;

	std::vector<BlockPart> elements;
	std::map<std::string, std::string> textures;

	bool isResolved() const;
	bool hasParent() const;

	ModelBlock& getParent() const;
protected:
	ModelBlock* mParent = nullptr;

	
};

void from_json(const nlohmann::json& json, ModelBlock& mb);