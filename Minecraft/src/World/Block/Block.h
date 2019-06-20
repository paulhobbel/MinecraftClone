#pragma once

#include "BlockId.h"

class BlockData;

struct Block
{
	Block() = default;
	Block(Block_t id);
	Block(BlockId id);

	bool operator ==(Block other) const
	{
		return id == other.id;
	}

	bool operator !=(Block other) const
	{
		return id != other.id;
	}

	Block_t id = 0;
};

