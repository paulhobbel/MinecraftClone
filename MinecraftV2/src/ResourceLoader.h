#pragma once

#include <map>

#include "Resources/ModelBlock.h"
#include "Renderer/Texture/AtlasTexture.h"

class ResourceLoader
{
public:
	ResourceLoader();

	void loadBlocks();

private:
	void registerTextures();

	std::map<std::string, ModelBlock> mBlocks;

	AtlasTexture* mAtlasTexture = nullptr;
};
