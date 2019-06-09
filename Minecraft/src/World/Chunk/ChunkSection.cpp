#include "ChunkSection.h"
#include "../World.h"

ChunkSection::ChunkSection(const glm::ivec3& position, World& world)
	: m_position(position), m_world(&world), m_aabb({ CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE })
{
	m_aabb.Update({ position.x * CHUNK_SIZE, position.y * CHUNK_SIZE, position.z * CHUNK_SIZE });
}

Block ChunkSection::GetBlock(int x, int y, int z) const noexcept
{
	if (OutOfBounds(x) || OutOfBounds(y) || OutOfBounds(z))
		return BlockId::Air;
	// TODO: Check if out of bounds!
	return m_blocks[GetBlockIndex(x, y, z)];
}

void ChunkSection::SetBlock(int x, int y, int z, Block block)
{
	// TODO: Check if out of bounds!
	m_blocks[GetBlockIndex(x, y, z)] = block;
}

bool ChunkSection::OutOfBounds(int value)
{
	return value >= CHUNK_SIZE || value < 0;
}

ChunkSection& ChunkSection::GetNeighbour(int x, int z)
{
	return m_world->GetChunkProvider()
		.GetChunk(m_position.x + x, m_position.z + z)
		.GetSection(m_position.y);
}

const glm::ivec3 ChunkSection::GetPosition() const
{
	return m_position;
}

bool ChunkSection::HasBuffered()
{
	return m_mesh.HasBuffered();
}

void ChunkSection::BufferMesh()
{
	m_mesh.BufferMesh();
}

bool ChunkSection::HasMesh()
{
	return m_hasMesh;
}

void ChunkSection::MakeMesh()
{
	ChunkMeshBuilder(*this, m_mesh).Build();
	m_mesh.SetHasBuffered(false);
	m_hasMesh = true;
}

const ChunkMesh& ChunkSection::GetMesh() const
{
	return m_mesh;
}

int ChunkSection::GetBlockIndex(int x, int y, int z)
{
	return y * CHUNK_AREA + z * CHUNK_SIZE + x;
}
