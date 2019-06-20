#pragma once
#include "../GameWindow.h"
#include "ChunkRenderer.h"

class ChunkSection;
class Camera;
class ResourceManager;

class MainRenderer
{
public:
	void init(const ResourceManager& resourceManager);
	void renderChunk(ChunkSection& section);
	void render(const GameWindow& window, const Camera& camera);
private:
	ChunkRenderer mChunkRenderer;
};
