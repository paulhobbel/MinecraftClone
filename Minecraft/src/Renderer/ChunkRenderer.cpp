#include <iostream>

#include <glm/vec3.hpp>

#include "../World/Chunk/Chunk.h"
#include "../World/Chunk/ChunkMesh.h"
#include "ChunkRenderer.h"
#include "../Camera.h"

#include "../Model.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

Texture dirtTexture;

ChunkRenderer::ChunkRenderer()
{
}

void ChunkRenderer::Init()
{
	m_shader.Create();

	dirtTexture.Create("res/textures/dirt.png");
}

void ChunkRenderer::AddMesh(const ChunkMesh& mesh)
{
	m_chunks.push_back(&mesh.GetModel().GetRenderInfo());
}

void ChunkRenderer::Render(Camera& camera)
{
	if (m_chunks.empty())
		return;

	m_shader.UseProgram();

	m_shader.LoadProjectionViewMatrix(camera.getProjectionViewMatrix());

	dirtTexture.Bind();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (auto info : m_chunks)
	{
		glBindVertexArray(info->vao);
		glDrawElements(GL_TRIANGLES, info->indicesCount, GL_UNSIGNED_INT, nullptr);
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLenum lastError = glGetError();

	if (lastError != GL_NO_ERROR)
		std::cout << "[ERROR/ChunkRenderer] GL Error: " << lastError << std::endl;

	m_chunks.clear();
}
