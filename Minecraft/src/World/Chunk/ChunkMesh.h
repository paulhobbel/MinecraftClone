#pragma once

#include <array>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>

#include "../../Mesh.h"

class ChunkMesh
{
public:
	ChunkMesh() = default;
	
	void AddFace(const std::array<GLfloat, 12>& blockFace,
		const std::array<GLfloat, 8> texCoords,
		const glm::vec3 chunkPosition,
		const glm::vec3 blockPosition);

	const Mesh GetMesh() const;

private:
	Mesh m_mesh;
};

