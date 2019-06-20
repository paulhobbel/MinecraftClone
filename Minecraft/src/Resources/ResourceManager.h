#pragma once

#include <map>

#include "ModelBlock.h"
#include "../Renderer/Texture/AtlasTexture.h"
#include "../World/Block/BlockFace.h"

enum BlockId : unsigned char;

class ResourceManager
{
public:
	ResourceManager();

	void loadBlocks();
	void loadBlockTextures();
	void uploadBlockAtlas() const;

	AtlasTexture& getAtlasTexture() const;

private:
	std::string getLocationById(BlockId id);
	BlockFaceEnum getFaceEnumByString(std::string face);

	std::map<std::string, std::shared_ptr<ModelBlock>> mBlocks;

	AtlasTexture* mAtlasTexture = nullptr;
};
