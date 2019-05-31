#pragma once

#include "ChunkRenderer.h"

class Camera;

class MainRenderer
{
public:
	void Render(Camera& camera);

private:
	ChunkRenderer m_chunkRenderer;
};

