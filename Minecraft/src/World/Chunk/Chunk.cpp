#include "Chunk.h"
#include "../Generation/Terrain/TerrainGenerator.h"

Chunk::Chunk(World& world, const Vec2& position)
	: m_world(&world), m_position(position)
{
}

Block Chunk::GetBlock(int x, int y, int z) const noexcept
{
	return Block();
}

void Chunk::SetBlock(int x, int y, int z, Block block)
{

}

bool Chunk::IsLoaded() const noexcept
{
	return m_loaded;
}

void Chunk::Load(TerrainGenerator& generator)
{
	if (m_loaded)
		return;

	generator.GenerateTerrain(*this);

	m_loaded = true;
}

ChunkSection& Chunk::GetSection(int index)
{
	// TODO: Add index out of bounds check

	return m_sections[index];
}

Vec2& Chunk::GetPosition()
{
	return m_position;
}
