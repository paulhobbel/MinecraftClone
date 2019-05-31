#include "ChunkMesh.h"

#include "../../Constants.h"


void ChunkMesh::AddFace(const std::array<GLfloat, 12>& blockFace, const std::array<GLfloat, 8> texCoords, const glm::vec3 chunkPosition, const glm::vec3 blockPosition)
{
	m_mesh.texCoords.insert(m_mesh.texCoords.end(), texCoords.begin(), texCoords.end());

	for (int i = 0, face = 0; i < 4; i++)
	{
		m_mesh.vertices.push_back(blockFace[face++] + chunkPosition.x * CHUNK_SIZE + blockPosition.x);
		m_mesh.vertices.push_back(blockFace[face++] + chunkPosition.y * CHUNK_SIZE + blockPosition.y);
		m_mesh.vertices.push_back(blockFace[face++] + chunkPosition.z * CHUNK_SIZE + blockPosition.z);
	}
}

const Mesh ChunkMesh::GetMesh() const
{
	return m_mesh;
}
