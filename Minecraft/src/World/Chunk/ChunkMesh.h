#pragma once

#include <array>
#include <vector>
#include <glm/vec3.hpp>
#include <glad/glad.h>

#include "../../Mesh.h"
#include "../../Model.h"

class ChunkMesh
{
public:
	ChunkMesh() = default;

	void AddFace(const std::array<GLfloat, 12>& blockFace,
		const std::array<GLfloat, 8> texCoords,
		const glm::vec3 chunkPosition,
		const glm::vec3 blockPosition,
		const GLfloat cardinalLight);

	void BufferMesh();

	Model& GetModel();

private:
	Mesh m_mesh;
	Model m_model;

	std::vector<GLfloat> m_lights;
	unsigned int m_indiceIndex = 0;
};

