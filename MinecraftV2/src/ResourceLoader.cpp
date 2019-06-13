#include <filesystem>
#include "ResourceLoader.h"

#include <iostream>
#include <queue>

#include "Resources/ModelBlock.h"

#include "Util/FileUtil.h"
#include "Util/Stopwatch.h"

void ResourceLoader::loadBlocks()
{
	Stopwatch stopwatch;

	std::cout << "[INFO/ResourceLoader] Loading blocks models [ res/models/blocks ]" << std::endl;
	for(const auto& entry : std::experimental::filesystem::directory_iterator("res/models/block"))
	{
		auto& path = entry.path();

		if(path.extension() != ".json")
			continue;

		ModelBlock block;
		if(!FileUtil::getContentsAsJson(path.string(), block))
		{
			std::cout << "[ERROR/ResourceLoader] Failed to load model [ " << path << " ]" << std::endl;
			continue;
		}

		block.id = "block/" + path.stem().string();

		mBlocks.emplace(block.id, block);
	};

	std::cout << "[INFO/ResourceLoader] Found " << mBlocks.size() << " model blocks, took " << stopwatch.reset() << "ms" << std::endl;

	std::queue<ModelBlock*> resolveQueue;

	for(auto& entry : mBlocks)
	{
		if(!entry.second.isResolved())
			resolveQueue.emplace(&entry.second);
	}

	while (!resolveQueue.empty())
	{
		auto& block = resolveQueue.front();
		if (block->isResolved())
		{
			resolveQueue.pop();
			continue;
		}

		auto& parent = mBlocks.at(block->parentLocation);
		if(!parent.isResolved())
		{
			resolveQueue.push(block);
			resolveQueue.push(&parent);
			resolveQueue.pop();
			continue;
		}

		block->mParent = &parent;
		resolveQueue.pop();
	}

	for (auto& entry : mBlocks)
	{
		std::cout << "[DEBUG/ResourceLoader] Model [ " << entry.first << " ] resolved? " << std::boolalpha << entry.second.isResolved() << std::endl;
	}

	std::cout << "[INFO/ResourceLoader] Resolved " << mBlocks.size() << " model blocks, took " << stopwatch.reset() << "ms" << std::endl;
}
