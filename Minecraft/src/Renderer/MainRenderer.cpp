#include "MainRenderer.h"
#include "../World/Chunk/ChunkSection.h"
#include "../Resources/ResourceManager.h"

void MainRenderer::init(const ResourceManager& resourceManager)
{
	mChunkRenderer.init(resourceManager);
}

void MainRenderer::renderChunk(ChunkSection& section)
{
	mChunkRenderer.addMesh(section.getMesh());
}

void MainRenderer::render(const GameWindow& window, const Camera& camera)
{
	glClearColor(.1f, .5f, 1.f, 1.f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	mChunkRenderer.render(camera);

	window.swapBuffers();
}
