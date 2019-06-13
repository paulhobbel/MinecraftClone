#include "ModelBlock.h"

bool ModelBlock::isResolved() const
{
	return !hasParent() || mParent != nullptr;
}

bool ModelBlock::hasParent() const
{
	return !parentLocation.empty();
}

ModelBlock& ModelBlock::getParent() const
{
	return *mParent;
}

void from_json(const nlohmann::json& json, ModelBlock& mb)
{
	if (json.contains("parent"))
	{
		mb.parentLocation = json.at("parent").get<std::string>();
	}

	if (json.contains("textures"))
	{
		mb.textures = json.at("textures").get<std::map<std::string, std::string>>();
	}

	if (json.contains("elements"))
		mb.elements = json.at("elements").get<std::vector<BlockPart>>();
}
