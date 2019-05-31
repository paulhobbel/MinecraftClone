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


	void TryAddFace(const std::array<GLfloat, 12>& blockFace, const glm::vec3& texCoords, const glm::vec3& blockPosition, const glm::vec3& blockFacing);
	bool ShouldMakeFace(const glm::vec3& blockPosition);

	ChunkSection* m_section;
	ChunkMesh* m_mesh;
	const Block* m_block = nullptr;
};