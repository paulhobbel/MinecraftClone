#include "ChunkSection.h"
#include "../World.h"

Block ChunkSection::GetBlock(int x, int y, int z) const noexcept
{
	// TODO: Check if out of bounds!
	return m_blocks[GetBlockIndex(x, y, z)];
}

void ChunkSection::SetBlock(int x, int y, int z, Block block)
{
	// TODO: Check if out of bounds!
	m_blocks[GetBlockIndex(x, y, z)] = block;
}

ChunkSection& ChunkSection::GetNeighbour(int x, int z)
{
	return m_world->GetChunkProvider()
		.GetChunk(m_position.x + x, m_position.z + z)
		.GetSection(m_position.y);
}

const glm::vec3 ChunkSection::GetPosition() const
{
	return m_position;
}

void ChunkSection::MakeMesh()
{
	ChunkMeshBuilder(*this, m_mesh).Build();
}

const ChunkMesh& ChunkSection::GetMesh() const
{
	return m_mesh;
}

int ChunkSection::GetBlockIndex(int x, int y, int z)
{
	return y * CHUNK_SIZE + z * CHUNK_SIZE + x;
}
