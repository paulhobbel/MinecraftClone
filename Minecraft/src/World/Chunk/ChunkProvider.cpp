#include "ChunkProvider.h"
#include "../Generation/Terrain/FlatTerrainGenerator.h"

ChunkProvider::ChunkProvider(World& world) : m_world(&world)
{
	m_generator = new FlatTerrainGenerator();
}

ChunkProvider::~ChunkProvider()
{
}

std::unordered_map<glm::ivec2, Chunk>& ChunkProvider::GetChunks()
{
	return m_chunks;
}

Chunk& ChunkProvider::GetChunk(int x, int z)
{
	glm::ivec2 position(x, z);

	if (!ChunkExists(x, z)) {
		Chunk chunk{ *m_world, {x, z} };
		m_chunks.emplace(position, std::move(chunk));
	}

	return m_chunks[position];
}

bool ChunkProvider::MakeMesh(int x, int z, const Camera& camera)
{
	for (int nx = -1; nx <= 1; nx++)
	{
		for (int nz = -1; nz <= 1; nz++)
		{
			LoadChunk(x + nx, z + nz);
		}
	}

	return GetChunk(x, z).MakeMesh(camera);
}

bool ChunkProvider::ChunkExists(int x, int z) const
{
	return m_chunks.find({ x, z }) != m_chunks.end();
}

void ChunkProvider::LoadChunk(int x, int z)
{
	GetChunk(x, z).Load(*m_generator);
}
