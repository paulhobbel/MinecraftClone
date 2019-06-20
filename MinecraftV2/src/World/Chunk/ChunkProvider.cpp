#include "ChunkProvider.h"
#include "../Generation/FlatTerrainGenerator.h"

ChunkProvider::ChunkProvider(World& world) : mWorld(&world)
{
	mGenerator = new FlatTerrainGenerator();
}

std::unordered_map<glm::ivec2, std::shared_ptr<Chunk>>& ChunkProvider::getChunks()
{
	return mChunks;
}

Chunk& ChunkProvider::getChunk(int x, int z)
{
	glm::ivec2 position(x, z);

	if (!chunkExists(x, z)) {
		mChunks.emplace(position, std::make_shared<Chunk>(*mWorld, position));
	}

	return *mChunks[position];
}

bool ChunkProvider::makeMesh(int x, int z, const Camera& camera)
{
	for (int nx = -1; nx <= 1; nx++)
	{
		for (int nz = -1; nz <= 1; nz++)
		{
			loadChunk(x + nx, z + nz);
		}
	}

	return getChunk(x, z).makeMesh(camera);
}

bool ChunkProvider::chunkExists(int x, int z) const
{
	return mChunks.find({ x, z }) != mChunks.end();
}

void ChunkProvider::loadChunk(int x, int z)
{
	getChunk(x, z).load(*mGenerator);
}
