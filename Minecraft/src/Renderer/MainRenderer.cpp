#include <glad/glad.h>

#include "../Camera.h"
#include "MainRenderer.h"

void MainRenderer::Render(Camera& camera)
{
	glClearColor(0.1, 0.5, 1.0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_chunkRenderer.Render(camera);
}
