#pragma once

#include "ChunkRenderer.h"

class Camera;

class MainRenderer
{
public:
	void PreRender(const Camera& camera);
	void Render(const Camera& camera);
	void PostRender(const Camera& camera);

private:
	ChunkRenderer m_chunkRenderer;
};

