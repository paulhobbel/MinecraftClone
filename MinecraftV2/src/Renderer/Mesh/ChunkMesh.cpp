#include "ChunkMesh.h"
#include <array>
#include <utility>
#include "../../Constants.h"
#include "../../World/Block/Block.h"
#include "../../World/Block/BlockRegistry.h"
#include "../../World/Chunk/ChunkSection.h"


void ChunkMesh::addFace(BlockFace bFace, glm::vec3 chunkPosition, glm::vec3 blockPosition)
{
	// Convert quad tex coords to triangle tex coords
	auto minUv = bFace.getSprite().getMinUv();
	auto maxUv = bFace.getSprite().getMaxUv();
	std::array<GLfloat, 8> tempTexCoords = {
		maxUv.x, maxUv.y,
		minUv.x, maxUv.y,
		minUv.x, minUv.y,
		maxUv.x, minUv.y
		};

	texCoords.insert(texCoords.end(), tempTexCoords.begin(), tempTexCoords.end());

	auto blockFace = bFace.getVertices();

	for (int i = 0, face = 0; i < 4; i++)
	{
		vertices.push_back(blockFace[face++] + chunkPosition.x * CHUNK_SIZE + blockPosition.x);
		vertices.push_back(blockFace[face++] + chunkPosition.y * CHUNK_SIZE + blockPosition.y);
		vertices.push_back(blockFace[face++] + chunkPosition.z * CHUNK_SIZE + blockPosition.z);
		lights.push_back(bFace.getLight());
	}

	indices.insert(indices.end(),
		{
			mIndiceIndex,
			mIndiceIndex + 1,
			mIndiceIndex + 2,
			mIndiceIndex + 2,
			mIndiceIndex + 3,
			mIndiceIndex
		});

	// TexCoord | LightValue
	mIndiceIndex += 4;
}

void ChunkMesh::setHasBuffered(bool flag)
{
	mBuffered = flag;
}

bool ChunkMesh::hasBuffered() const
{
	return mBuffered;
}

ChunkMesh::Builder::Builder(ChunkSection& section, ChunkMesh& mesh) : mSection(&section), mMesh(&mesh)
{
}

struct AdjacentBlockPositions
{
	void Update(int x, int y, int z)
	{
		up = { x,     y + 1,  z };
		down = { x,     y - 1,  z };
		left = { x - 1, y,      z };
		right = { x + 1, y,      z };
		front = { x,     y,      z + 1 };
		back = { x,     y,      z - 1 };
	}

	glm::ivec3 up;
	glm::ivec3 down;
	glm::ivec3 left;
	glm::ivec3 right;
	glm::ivec3 front;
	glm::ivec3 back;
};

void ChunkMesh::Builder::build()
{
	BlockRegistry& registry = BlockRegistry::instance();
	AdjacentBlockPositions directions;
	mBlock = mSection->begin();

	//auto startTime = std::chrono::steady_clock::now();

	for (int16_t i = 0; i < CHUNK_VOLUME; i++)
	{
		// Get X / Y / Z
		uint8_t x = i % CHUNK_SIZE;
		uint8_t y = i / (CHUNK_SIZE * CHUNK_SIZE);
		uint8_t z = (i / CHUNK_SIZE) % CHUNK_SIZE;

		Block block = *mBlock;


		if (block == BlockId::Air)
			continue;

		glm::vec3 position(x, y, z);

		directions.Update(x, y, z);

		auto data = registry.getBlockData(static_cast<BlockId>(block.id));

		//if ((m_section->GetPosition().y != 0) || y != 0)
		tryAddFace(data->getFace(DOWN), position, directions.down);
		tryAddFace(data->getFace(UP), position, directions.up);

		tryAddFace(data->getFace(WEST), position, directions.left);
		tryAddFace(data->getFace(EAST), position, directions.right);

		tryAddFace(data->getFace(SOUTH), position, directions.front);
		tryAddFace(data->getFace(NORTH), position, directions.back);

		mBlock++;
	}
}

void ChunkMesh::Builder::tryAddFace(BlockFace face, glm::vec3 blockPosition, glm::vec3 blockFacing)
{
	if (shouldMakeFace(blockFacing, *mBlock))
	{
		mMesh->addFace(std::move(face), mSection->getPosition(), blockPosition);
	}
}

bool ChunkMesh::Builder::shouldMakeFace(const glm::ivec3& blockPosition, const Block& block)
{
	const auto blockAdj = mSection->getBlock(blockPosition.x, blockPosition.y, blockPosition.z);

	if (blockAdj == BlockId::Air)
		return true;

	//if (blockAdj != block)
	//	return true;

	// TODO: Add more checks

	return false;
}
