#pragma once

#include <array>

#include <glad/glad.h>
#include <glm/vec3.hpp>

class ChunkSection;
class ChunkMesh;
struct Block;

class ChunkMeshBuilder
{
public:
	ChunkMeshBuilder(ChunkSection& section, ChunkMesh& mesh);

	void Build();

private:


	void TryAddFace(const std::array<GLfloat, 12>& blockFace, const glm::vec3& texCoords, const glm::ivec3& blockPosition, const glm::ivec3& blockFacing, GLfloat cardinalLight);
	bool ShouldMakeFace(const glm::ivec3& blockPosition);

	ChunkSection* m_section;
	ChunkMesh* m_mesh;
	const Block* m_block = nullptr;
};