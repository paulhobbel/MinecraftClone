#include <glad/glad.h>

#include "../Camera.h"
#include "MainRenderer.h"

void MainRenderer::Init()
{
	m_chunkRenderer.Init();
}

void MainRenderer::Render(Camera& camera)
{
	glClearColor(.1f, .5f, 1.f, 1.f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_chunkRenderer.Render(camera);
}
