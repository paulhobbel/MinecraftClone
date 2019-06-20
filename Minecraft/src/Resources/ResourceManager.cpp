#include <filesystem>
#include <iostream>
#include <queue>
#include <set>

#include "ResourceManager.h"

#include "../Util/FileUtil.h"
#include "../Util/Stopwatch.h"
#include "../World/Block/BlockId.h"
#include "../World/Block/BlockRegistry.h"

ResourceManager::ResourceManager()
{
	mAtlasTexture = new AtlasTexture();
}

void ResourceManager::loadBlocks()
{
	Stopwatch stopwatch;

	std::cout << "[INFO/ResourceManager] Loading blocks models [ res/models/blocks ]" << std::endl;

	std::map<std::string, std::shared_ptr<ModelBlock>> unresolvedBlocks;

	for(const auto& entry : std::experimental::filesystem::directory_iterator("res/models/block"))
	{
		auto& path = entry.path();

		if(path.extension() != ".json")
			continue;

		ModelBlock block;
		if(!FileUtil::getContentsAsJson(path.string(), block))
		{
			std::cout << "[ERROR/ResourceManager] Failed to load model [ " << path << " ]" << std::endl;
			continue;
		}

		block.id = "block/" + path.stem().string();

		unresolvedBlocks.emplace(block.id, std::make_shared<ModelBlock>(block));
	};

	std::cout << "[INFO/ResourceManager] Found " << unresolvedBlocks.size() << " model blocks, took " << stopwatch.reset() << "ms" << std::endl;

	std::queue<std::shared_ptr<ModelBlock>> resolveQueue;

	for(auto& entry : unresolvedBlocks)
	{
		if(!entry.second->isResolved())
			resolveQueue.push(entry.second);
	}

	while (!resolveQueue.empty())
	{
		auto& block = resolveQueue.front();
		if (block->isResolved())
		{
			resolveQueue.pop();
			continue;
		}

		auto& parent = unresolvedBlocks.at(block->parentLocation);
		if(!parent->isResolved())
		{
			resolveQueue.pop();
			resolveQueue.push(block);
			resolveQueue.push(parent);
			continue;
		}

		block->mParent = parent;
		resolveQueue.pop();
	}

	for(auto& entry : unresolvedBlocks)
	{
		if (entry.second->isResolved())
			mBlocks.emplace(entry.first, entry.second);
	}

	std::cout << "[INFO/ResourceManager] Resolved " << mBlocks.size() << " model blocks, took " << stopwatch.reset() << "ms" << std::endl;
}

void ResourceManager::loadBlockTextures()
{
	Stopwatch stopwatch;
	std::set<std::string> textures;

	auto& registry = BlockRegistry::instance();

	for(int i = 0; i < BlockId::NUM_BLOCKS; i++)
	{
		auto location = getLocationById(static_cast<BlockId>(i));
		if(location == "noexists")
			continue;

		if(mBlocks.find(location) == mBlocks.end())
			continue;

		auto block = mBlocks.at(location);
		auto bData = registry.getBlockData(static_cast<BlockId>(i));

		for (auto& element : block->getElements())
		{
			for (auto& face : element.faces)
			{
				std::string resolvedTexture = block->resolveTexture(face.second.texture);
				if (resolvedTexture == "noexists")
					continue;

				auto& bFace = bData->getFace(getFaceEnumByString(face.first));

				bFace.setSprite(mAtlasTexture->registerSprite(resolvedTexture));
				textures.emplace(resolvedTexture);
			}
		}
	}

	std::cout << "[INFO/ResourceManager] Resolved " << textures.size() << " textures, took " << stopwatch.reset() << "ms" << std::endl;

	mAtlasTexture->stitch();

	std::cout << "[INFO/ResourceManager] Compiled atlas texture, took " << stopwatch.reset() << "ms" << std::endl;
}

std::string ResourceManager::getLocationById(BlockId id)
{
	switch (id)
	{
	case Dirt:
		return "block/dirt";
	case Grass:
		return "block/grass";
	case Stone:
		return "block/stone";
	case OakLog:
		return "block/oak_log";
	case WhiteWool:
		return "block/white_wool";

	}

	return "noexists";
}

BlockFaceEnum ResourceManager::getFaceEnumByString(std::string face)
{
	if (face == "north")
		return BlockFaceEnum::NORTH;

	if (face == "east")
		return BlockFaceEnum::EAST;

	if (face == "south")
		return BlockFaceEnum::SOUTH;

	if (face == "west")
		return BlockFaceEnum::WEST;

	if (face == "up")
		return BlockFaceEnum::UP;

	if (face == "down")
		return BlockFaceEnum::DOWN;
}

void ResourceManager::uploadBlockAtlas() const
{
	mAtlasTexture->upload();
}

AtlasTexture& ResourceManager::getAtlasTexture() const
{
	return *mAtlasTexture;
}
