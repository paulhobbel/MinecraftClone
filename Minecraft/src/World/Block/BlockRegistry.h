#pragma once
#include <map>
#include <string>
#include "BlockId.h"
#include "BlockData.h"
#include <memory>

class BlockRegistry
{
public:
	static BlockRegistry& instance();

	size_t getNumBlocks();

	std::shared_ptr<BlockData> getBlockData(BlockId block);

private:
	BlockRegistry();

	std::map<BlockId, std::shared_ptr<BlockData>> mBlocks;
};
