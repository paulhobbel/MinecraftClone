#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include <glad/glad.h>

#include "../Camera.h"
#include "MainRenderer.h"
#include "../World/Chunk/ChunkSection.h"

void MainRenderer::Init()
{
	m_chunkRenderer.Init();
}

void MainRenderer::RenderChunk(const ChunkSection& section)
{
	m_chunkRenderer.AddMesh(section.GetMesh());
}

void MainRenderer::Render(Camera& camera)
{
	glClearColor(.1f, .5f, 1.f, 1.f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_chunkRenderer.Render(camera);
}
