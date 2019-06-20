#pragma once

#include <array>
#include <glm/vec3.hpp>

#include "../Block/Block.h"

#include "../../AABB.h"
#include "../../Renderer/Mesh/ChunkMesh.h"
#include "../../Constants.h"

class World;

class ChunkSection
{
	friend class Chunk;
public:
	ChunkSection(const glm::ivec3& position, World& world);

	Block getBlock(int x, int y, int z) const noexcept;
	void setBlock(int x, int y, int z, Block block);

	ChunkSection& getNeighbour(int x, int z);

	glm::ivec3 getPosition() const;

	bool hasBuffered();
	void bufferMesh();

	bool hasMesh() const;
	void makeMesh();
	std::shared_ptr<ChunkMesh> getMesh() const;

	const Block* begin() { return &mBlocks[0]; }
	//std::array<Block, CHUNK_VOLUME> getBlocks();

private:

	static bool outOfBounds(int value);
	static int getBlockIndex(int x, int y, int z);

	AABB mAabb;
	glm::ivec3 mPosition;

	std::array<Block, CHUNK_VOLUME> mBlocks;
		//std::array<Block, CHUNK_VOLUME> mBlocks;

	bool mHasMesh = false;
	//ChunkMesh mMesh;
	std::shared_ptr<ChunkMesh> mMesh;

	World* mWorld;
};