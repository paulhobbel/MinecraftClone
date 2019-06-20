#pragma once
#include <array>
#include "BlockFace.h"

enum BlockType
{
	INVISIBLE = 0,
	SOLID = 1
};

//enum BlockFace
//{
//	UP,
//	DOWN,
//	NORTH,
//	EAST,
//	SOUTH,
//	WEST,
//
//	NUM_FACES
//};

class BlockData
{
public:
	BlockData(BlockType type);

	BlockType getType();
	//std::array<int, 12> getFace(BlockFace face);
	BlockFace& getFace(BlockFaceEnum face);

private:
	BlockType mType;
	std::array<BlockFace, NUM_FACES> mFaces;

};
