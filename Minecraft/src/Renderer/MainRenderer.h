#pragma once

#include "ChunkRenderer.h"
#include "../Initializable.h"

class Camera;

class MainRenderer : public Initializable
{
public:
	void Init() override;
	void Render(Camera& camera);

private:
	ChunkRenderer m_chunkRenderer;
};

