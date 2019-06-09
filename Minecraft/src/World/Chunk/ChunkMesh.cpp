#include "ChunkMesh.h"

#include "../../Constants.h"

void ChunkMesh::AddFace(const std::array<GLfloat, 12>& blockFace, const std::array<GLfloat, 8> texCoords, const glm::vec3 chunkPosition, const glm::vec3 blockPosition, GLfloat cardinalLight)
{
	m_mesh.texCoords.insert(m_mesh.texCoords.end(), texCoords.begin(), texCoords.end());

	for (int i = 0, face = 0; i < 4; i++)
	{
		m_mesh.vertices.push_back(blockFace[face++] + chunkPosition.x * CHUNK_SIZE + blockPosition.x);
		m_mesh.vertices.push_back(blockFace[face++] + chunkPosition.y * CHUNK_SIZE + blockPosition.y);
		m_mesh.vertices.push_back(blockFace[face++] + chunkPosition.z * CHUNK_SIZE + blockPosition.z);
		m_lights.push_back(cardinalLight);
	}

	m_mesh.indices.insert(m_mesh.indices.end(),
		{
			m_indiceIndex,
			m_indiceIndex + 1,
			m_indiceIndex + 2,
			m_indiceIndex + 2,
			m_indiceIndex + 3,
			m_indiceIndex
		});

	// TexCoord | LightValue
	m_indiceIndex += 4;

	//m_buffered = false;
}

void ChunkMesh::SetHasBuffered(bool flag)
{
	m_buffered = flag;
}

bool ChunkMesh::HasBuffered()
{
	return m_buffered;
}

void ChunkMesh::BufferMesh()
{
	m_model.Create(m_mesh);
	m_model.AddVBO(1, m_lights);

	m_mesh.indices.clear();
	m_mesh.vertices.clear();
	m_mesh.texCoords.clear();

	m_mesh.indices.shrink_to_fit();
	m_mesh.vertices.shrink_to_fit();
	m_mesh.texCoords.shrink_to_fit();

	m_indiceIndex = 0;

	m_buffered = true;
}

const Model& ChunkMesh::GetModel() const
{
	return m_model;
}
