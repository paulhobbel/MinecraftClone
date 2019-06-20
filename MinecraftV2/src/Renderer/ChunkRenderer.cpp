#include "ChunkRenderer.h"
#include "../Camera.h"
#include <iostream>
#include "../Resources/ResourceManager.h"
#include "Texture/AtlasTexture.h"

void ChunkRenderer::init(const ResourceManager& resourceManager)
{
	mShader.create();
	mTexture = &resourceManager.getAtlasTexture();

	testTexture.loadFromFileS("res/textures/blocks/dirt.png");
}

void ChunkRenderer::addMesh(const ChunkMesh& mesh)
{
	mChunks.push_back(&mesh);
}

void ChunkRenderer::render(const Camera& camera)
{
	if (mChunks.empty())
		return;

	mShader.useProgram();

	mShader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());

	mTexture->bind();
	//glBindTexture(GL_TEXTURE_2D, mTexture->getId());
	//glColor3f(0.1, 1.0, 1.0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (auto& mesh : mChunks)
	{
		if (mesh->getIndicesCount() == 0)
		{
			//std::cout << "[WARN/ChunkRenderer] Tried rendering a chunk section with 0 indices, did something break?" << std::endl;
			continue;
		}

		//mesh->bindVao();
		glBindVertexArray(mesh->mVao);
		glDrawElements(GL_TRIANGLES, mesh->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLenum lastError = glGetError();

	if (lastError != GL_NO_ERROR)
		std::cout << "[ERROR/ChunkRenderer] GL Error: " << lastError << std::endl;

	mChunks.clear();
}
