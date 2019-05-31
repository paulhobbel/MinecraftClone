#pragma once

#include <array>
#include <glm/vec3.hpp>

#include "ChunkMesh.h"
#include "ChunkMeshBuilder.h"
#include "../Block/Block.h"
#include "../../Constants.h"

class World;

class ChunkSection
{
	friend class Chunk;
public:
	Block GetBlock(int x, int y, int z) const noexcept;
	void SetBlock(int x, int y, int z, Block block);

	ChunkSection& GetNeighbour(int x, int z);

	const glm::vec3 GetPosition() const;


	void MakeMesh();
	const ChunkMesh& GetMesh() const;

	const Block* Begin() { return &m_blocks[0]; }

private:
	static int GetBlockIndex(int x, int y, int z);

	glm::vec3 m_position;

	std::array<Block, CHUNK_VOLUME> m_blocks;

	ChunkMesh m_mesh;
	World* m_world;
};