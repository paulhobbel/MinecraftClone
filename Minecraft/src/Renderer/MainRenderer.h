#pragma once

#include "ChunkRenderer.h"
#include "../Initializable.h"

class ChunkSection;
class Camera;

class MainRenderer : public Initializable
{
public:
	void Init() override;
	void RenderChunk(const ChunkSection& mesh);
	void Render(Camera& camera);

private:
	ChunkRenderer m_chunkRenderer;
};

