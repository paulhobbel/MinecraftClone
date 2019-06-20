#include "ChunkSection.h"
#include "../World.h"
#include "../../Util/PositionUtil.h"
#include "../../Renderer/Mesh/ChunkMesh.h"
#include "../../Constants.h"

ChunkSection::ChunkSection(const glm::ivec3& position, World& world)
	: mAabb({CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE}), mPosition(position), mWorld(&world)
{
	mAabb.update({position.x * CHUNK_SIZE, position.y * CHUNK_SIZE, position.z * CHUNK_SIZE});
	mMesh = std::make_shared<ChunkMesh>();
}

Block ChunkSection::getBlock(int x, int y, int z) const noexcept
{
	if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
	{
		auto worldBlockPos = PositionUtil::sectionToWorldBlockPosition(mPosition, x, y, z);

		return mWorld->getBlock(worldBlockPos.x, worldBlockPos.y, worldBlockPos.z);
	}

	return mBlocks[getBlockIndex(x, y, z)];
}

void ChunkSection::setBlock(int x, int y, int z, Block block)
{
	if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
	{
		auto worldBlockPos = PositionUtil::sectionToWorldBlockPosition(mPosition, x, y, z);

		mWorld->setBlock(worldBlockPos.x, worldBlockPos.y, worldBlockPos.z, block);
	}

	mBlocks[getBlockIndex(x, y, z)] = block;
}

bool ChunkSection::outOfBounds(int value)
{
	return value >= CHUNK_SIZE || value < 0;
}

ChunkSection& ChunkSection::getNeighbour(int x, int z)
{
	return *mWorld->getChunkProvider()
		.getChunk(mPosition.x + x, mPosition.z + z)
		.getSection(mPosition.y);
}

glm::ivec3 ChunkSection::getPosition() const
{
	return mPosition;
}

bool ChunkSection::hasBuffered()
{
	return mMesh->hasBuffered();
}

void ChunkSection::bufferMesh()
{
	mMesh->bufferMesh();
	mMesh->setHasBuffered(true);
}

bool ChunkSection::hasMesh() const
{
	return mHasMesh;
}

void ChunkSection::makeMesh()
{
	ChunkMesh::Builder(*this, *mMesh).build();
	mMesh->setHasBuffered(false);
	mHasMesh = true;
}

std::shared_ptr<ChunkMesh> ChunkSection::getMesh() const
{
	return mMesh;
}

int ChunkSection::getBlockIndex(int x, int y, int z)
{
	return y * CHUNK_AREA + z * CHUNK_SIZE + x;
}
