#pragma once

#include <cstdint>

using Block_t = uint8_t;

enum class BlockId : Block_t
{
	Air		= 0,
	Grass	= 1,
	Dirt	= 2,
	Stone	= 3,
	Sand	= 4
};