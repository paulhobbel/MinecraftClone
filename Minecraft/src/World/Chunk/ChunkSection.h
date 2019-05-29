#pragma once

#include <array>
#include <glm/vec3.hpp>

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

private:
	static int GetBlockIndex(int x, int y, int z);

	glm::vec3 m_position;

	std::array<Block, CHUNK_VOLUME> m_blocks;

	World* m_world;
};