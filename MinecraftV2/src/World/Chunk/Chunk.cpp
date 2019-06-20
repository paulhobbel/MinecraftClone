#include <glm/vec3.hpp>
#include "Chunk.h"
#include "../Generation/TerrainGenerator.h"
#include "../../Camera.h"
#include "../../Renderer/MainRenderer.h"
#include "../../Constants.h"
#include "../World.h"

Chunk::Chunk(World& world, const glm::ivec2& position)
	: mWorld(&world), mPosition(position)
{
}

Block Chunk::getBlock(int x, int y, int z) const noexcept
{
	if (outOfBounds(x, y, z))
		return BlockId::Air;

	return mSections[y / CHUNK_SIZE].getBlock(x, y % CHUNK_SIZE, z);
}

void Chunk::setBlock(int x, int y, int z, Block block)
{
	// Make sure enough sections are made, aka allocation....
	int sIndex = (y / CHUNK_SIZE) + 1;

	while (static_cast<int>(mSections.size()) < sIndex)
	{
		int y = mSections.size();
		mSections.emplace_back(glm::ivec3(mPosition.x, y, mPosition.y), *mWorld);
	}

	if (outOfBounds(x, y, z))
		return;

	mSections[y / CHUNK_SIZE].setBlock(x, y % CHUNK_SIZE, z, block);
}

bool Chunk::isLoaded() const noexcept
{
	return mLoaded;
}

void Chunk::load(TerrainGenerator& generator)
{
	if (mLoaded)
		return;

	generator.generateTerrain(*this);

	mLoaded = true;
}

bool Chunk::makeMesh(const Camera& camera)
{
	for (auto& section : mSections)
	{
		if (!section.hasMesh() && camera.getFrustum().isBoxInFrustum(section.mAabb))
		{
			// Check if mesh wasn't already generated
			// Check if section is even visible
			section.makeMesh();
			return true;
		}
	}
	return false;
}

void Chunk::render(MainRenderer& renderer, const Camera& camera)
{
	for (auto& section : mSections)
	{
		// Check if mesh is generated
		// Check if section is even visible
	
		if (!section.hasBuffered())
		{
			section.bufferMesh();
		}
		
		if(camera.getFrustum().isBoxInFrustum(section.mAabb))
			renderer.renderChunk(section);
	}
}

bool Chunk::outOfBounds(int x, int y, int z) const noexcept
{
	if (x >= CHUNK_SIZE || z >= CHUNK_SIZE)
		return true;

	if (x < 0 || y < 0 || z < 0)
	//	return true;
	//if (y < 0)
		return true;

	if (y >= (int)mSections.size() * CHUNK_SIZE)
		return true;

	return false;
}

ChunkSection& Chunk::getSection(int index)
{
	// TODO: Add index out of bounds check

	return mSections[index];
}

glm::ivec2& Chunk::getPosition()
{
	return mPosition;
}
