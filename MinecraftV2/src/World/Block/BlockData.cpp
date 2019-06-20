#include "BlockData.h"
#include <glad/glad.h>


//const std::array<GLfloat, 12> frontFace
//{
//	0, 0, 1,
//	1, 0, 1,
//	1, 1, 1,
//	0, 1, 1
//};
//
//const std::array<GLfloat, 12> backFace
//{
//	1, 0, 0,
//	0, 0, 0,
//	0, 1, 0,
//	1, 1, 0
//};
//
//const std::array<GLfloat, 12> leftFace
//{
//	0, 0, 0,
//	0, 0, 1,
//	0, 1, 1,
//	0, 1, 0
//};
//
//const std::array<GLfloat, 12> rightFace
//{
//	1, 0, 1,
//	1, 0, 0,
//	1, 1, 0,
//	1, 1, 1
//};
//
//const std::array<GLfloat, 12> topFace
//{
//	0, 1, 1,
//	1, 1, 1,
//	1, 1, 0,
//	0, 1, 0
//};
//
//const std::array<GLfloat, 12> bottomFace
//{
//	0, 0, 0,
//	1, 0, 0,
//	1, 0, 1,
//	0, 0, 1
//};

namespace
{
	constexpr GLfloat LIGHT_TOP = 1.0f;
	constexpr GLfloat LIGHT_X = 0.8f;
	constexpr GLfloat LIGHT_Z = 0.6f;
	constexpr GLfloat LIGHT_BOT = 0.4f;
}

BlockData::BlockData(BlockType type)
{
	mFaces[UP] = BlockFace({
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0
	}, LIGHT_TOP);

	mFaces[DOWN] = BlockFace({
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	}, LIGHT_BOT);

	mFaces[NORTH] = BlockFace({
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0
	}, LIGHT_Z);

	mFaces[EAST] = BlockFace({
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1
	}, LIGHT_X);

	mFaces[SOUTH] = BlockFace({
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1
	}, LIGHT_Z);

	mFaces[WEST] = BlockFace({
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0
	}, LIGHT_X);
}

BlockType BlockData::getType()
{
	return mType;
}

BlockFace& BlockData::getFace(BlockFaceEnum face)
{
	return mFaces[face];
}
