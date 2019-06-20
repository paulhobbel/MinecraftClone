#pragma once

#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

#include "BlockPart.h"

class ResourceManager;

class ModelBlock
{
	friend class ResourceManager;
public:
	std::string id;
	std::string parentLocation;

	std::vector<BlockPart> elements;
	std::map<std::string, std::string> textures;

	std::vector<BlockPart> getElements() const;

	std::string resolveTexture(const std::string& name) noexcept;

	bool isResolved() const;
	bool hasParent() const;

	ModelBlock& getParent() const;


	bool operator==(const ModelBlock& lhs) const
	{
		return lhs.id == id;
	}

protected:
	std::shared_ptr<ModelBlock> mParent = nullptr;

private:
	struct LookupRegistry
	{
		ModelBlock* model;
		ModelBlock* extModel;
	};

	std::string resolveTexture(const std::string& name, LookupRegistry* registry);

	
	
};

void from_json(const nlohmann::json& json, ModelBlock& mb);