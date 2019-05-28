#include "ChuckProvider.h"

ChuckProvider::ChuckProvider(World& world) : m_world(&world)
{
}

Chunk& ChuckProvider::GetChunk(int x, int y)
{
	Vec2 position(x, y);

	if (!ChunkExists(x, y)) {
		// TODO: Add new chunk
	}

	return m_chunks[position];
}

bool ChuckProvider::ChunkExists(int x, int y) const
{
	return m_chunks.find({ x, y }) != m_chunks.end();
}
