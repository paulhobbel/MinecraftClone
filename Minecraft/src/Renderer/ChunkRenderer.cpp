#include <GLFW/glfw3.h>

#include "../World/Chunk/ChunkMesh.h"
#include "ChunkRenderer.h"

void ChunkRenderer::Add(const ChunkMesh& mesh)
{
	m_chunks.push_back(mesh);
}

void ChunkRenderer::Render(const Camera& camera)
{
	if (m_chunks.empty())
	{
		return;
	}

	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);

	// Bind textures

	for (auto& mesh : m_chunks)
	{
		// Render mesh
	}

	m_chunks.clear();
}
