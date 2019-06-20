#include "ModelBlock.h"
#include <iostream>

bool startsWithHash(const std::string& name)
{
	return name.find('#') == 0;
}

std::vector<BlockPart> ModelBlock::getElements() const
{
	return elements.empty() && hasParent() ? mParent->getElements() : elements;
}

std::string ModelBlock::resolveTexture(const std::string& name) noexcept
{
	std::string textureName = name;
	if (!startsWithHash(textureName))
		textureName = "#" + textureName;

	return resolveTexture(textureName, new LookupRegistry { this, nullptr });
}

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

std::string ModelBlock::resolveTexture(const std::string& name, LookupRegistry* registry)
{
	if (!startsWithHash(name))
		return name;

	if(registry->extModel == this)
	{
		std::cout << "[WARN/ModelBlock] Unable to resolve texture due to upward reference: " << name << " in " << id << std::endl;
		return "noexists";
	}

	std::string textureName = textures[name.substr(1)];

	if (textureName.empty() && hasParent())
		textureName = mParent->resolveTexture(name, registry);

	registry->extModel = this;

	if (!textureName.empty() && startsWithHash(textureName))
		textureName = registry->model->resolveTexture(textureName, registry);

	return !textureName.empty() && !startsWithHash(textureName) ? textureName : "noexists";
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
