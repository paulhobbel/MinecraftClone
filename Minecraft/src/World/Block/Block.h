#pragma once

#include "BlockId.h"
#include "BlockData.h"

struct Block
{
	Block() = default;
	Block(Block_t id);
	Block(BlockId id);
	//Block(BlockId id, BlockData data);

	bool operator ==(Block other) const
	{
		return id == other.id;
	}

	bool operator !=(Block other) const
	{
		return id != other.id;
	}

	Block_t id = 0;
	//BlockData data;
};
