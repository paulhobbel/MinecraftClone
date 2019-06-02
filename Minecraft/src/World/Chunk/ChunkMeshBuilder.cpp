#include <iostream>
#include <chrono>

#include "ChunkMeshBuilder.h"
#include "ChunkSection.h"
#include "../Block/Block.h"

namespace
{
	const std::array<GLfloat, 12> frontFace
	{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1
	};

	const std::array<GLfloat, 12> backFace
	{
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0
	};

	const std::array<GLfloat, 12> leftFace
	{
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0
	};

	const std::array<GLfloat, 12> rightFace
	{
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1
	};

	const std::array<GLfloat, 12> topFace
	{
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0
	};

	const std::array<GLfloat, 12> bottomFace
	{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	};

	constexpr GLfloat LIGHT_TOP = 1.0f;
	constexpr GLfloat LIGHT_X = 0.8f;
	constexpr GLfloat LIGHT_Z = 0.6f;
	constexpr GLfloat LIGHT_BOT = 0.4f;
}

struct AdjacentBlockPositions
{
	void Update(int x, int y, int z)
	{
		up =	{ x,     y + 1,  z };
		down =	{ x,     y - 1,  z };
		left =	{ x - 1, y,      z };
		right = { x + 1, y,      z };
		front = { x,     y,      z + 1 };
		back =	{ x,     y,      z - 1 };
	}

	glm::ivec3 up;
	glm::ivec3 down;
	glm::ivec3 left;
	glm::ivec3 right;
	glm::ivec3 front;
	glm::ivec3 back;
};

ChunkMeshBuilder::ChunkMeshBuilder(ChunkSection& section, ChunkMesh& mesh) : m_section(&section), m_mesh(&mesh)
{
	m_block = nullptr;
}

void ChunkMeshBuilder::Build()
{
	AdjacentBlockPositions directions;
	m_block = m_section->Begin();

	//auto startTime = std::chrono::steady_clock::now();

	for (int16_t i = 0; i < CHUNK_VOLUME; i++)
	{
		// Get X / Y / Z
		uint8_t x = i % CHUNK_SIZE;
		uint8_t y = i / (CHUNK_SIZE * CHUNK_SIZE);
		uint8_t z = (i / CHUNK_SIZE) % CHUNK_SIZE;

		Block block = *m_block;
		

		if (block == BlockId::Air)
			continue;

		glm::vec3 position(x, y, z);

		directions.Update(x, y, z);

		//if ((m_section->GetPosition().y != 0) || y != 0)
		TryAddFace(bottomFace, position, position, directions.down, LIGHT_BOT);
		TryAddFace(topFace, position, position, directions.up, LIGHT_TOP);

		TryAddFace(leftFace, position, position, directions.left, LIGHT_X);
		TryAddFace(rightFace, position, position, directions.right, LIGHT_X);

		TryAddFace(frontFace, position, position, directions.front, LIGHT_Z);
		TryAddFace(backFace, position, position, directions.back, LIGHT_Z);

		m_block++;
	}

	//std::cout << "[Debug/ChunkMeshBuilder] Build mesh in " << std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - startTime).count() << "ms" << std::endl;
}

void ChunkMeshBuilder::TryAddFace(const std::array<GLfloat, 12>& blockFace, const glm::vec3& texCoords, const glm::ivec3& blockPosition, const glm::ivec3& blockFacing, GLfloat cardinalLight)
{
	if (ShouldMakeFace(blockFacing, *m_block))
	{
		m_mesh->AddFace(blockFace, { 0, 1, 1, 1, 1, 0, 0, 0 }, m_section->GetPosition(), blockPosition, cardinalLight);
	}
}

bool ChunkMeshBuilder::ShouldMakeFace(const glm::ivec3& blockPosition, const Block& block)
{
	auto blockAdj = m_section->GetBlock(blockPosition.x, blockPosition.y, blockPosition.z);

	if (blockAdj == BlockId::Air)
		return true;

	if (blockAdj != block)
		return true;

	// TODO: Add more checks

	return false;
}
