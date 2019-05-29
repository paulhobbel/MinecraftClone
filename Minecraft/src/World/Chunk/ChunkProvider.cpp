#include "ChunkProvider.h"
#include "../Generation/Terrain/FlatTerrainGenerator.h"

ChunkProvider::ChunkProvider(World& world) : m_world(&world)
{
	m_generator = new FlatTerrainGenerator();
}

ChunkProvider::~ChunkProvider()
{
}

Chunk& ChunkProvider::GetChunk(int x, int y)
{
	Vec2 position(x, y);

	if (!ChunkExists(x, y)) {
		Chunk chunk{ *m_world, {x, y} };
		m_chunks.emplace(position, std::move(chunk));
	}

	return m_chunks[position];
}

bool ChunkProvider::ChunkExists(int x, int y) const
{
	return m_chunks.find({ x, y }) != m_chunks.end();
}

void ChunkProvider::LoadChunk(int x, int y)
{
	GetChunk(x, y).Load(*m_generator);
}
