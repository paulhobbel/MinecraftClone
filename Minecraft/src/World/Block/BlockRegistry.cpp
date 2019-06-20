#include "BlockRegistry.h"

BlockRegistry& BlockRegistry::instance()
{
	static BlockRegistry instance;

	return instance;
}

size_t BlockRegistry::getNumBlocks()
{
	return mBlocks.size();
}

std::shared_ptr<BlockData> BlockRegistry::getBlockData(BlockId block)
{
	return mBlocks.at(block);
}

BlockRegistry::BlockRegistry()
{
	mBlocks.emplace(BlockId::Grass, std::make_shared<BlockData>(BlockType::SOLID));
	mBlocks.emplace(BlockId::Dirt, std::make_shared<BlockData>(BlockType::SOLID));
	mBlocks.emplace(BlockId::Stone, std::make_shared<BlockData>(BlockType::SOLID));
	mBlocks.emplace(BlockId::OakLog, std::make_shared<BlockData>(BlockType::SOLID));
	mBlocks.emplace(BlockId::WhiteWool, std::make_shared<BlockData>(BlockType::SOLID));
}
