#pragma once

#include <cstdint>

using Block_t = uint8_t;

enum BlockId : Block_t
{
	Air,
	Grass,
	Dirt,
	Stone,
	Sand,

	NUM_BLOCKS
};