#include "Block.h"

Block::Block(Block_t id)
	: id(id)
{
}

Block::Block(BlockId id)
	: id(static_cast<Block_t>(id))
{
}
