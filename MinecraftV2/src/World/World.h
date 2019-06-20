#pragma once

#include <atomic>
#include <thread>
#include <mutex>
#include <vector>

#include "Chunk/ChunkProvider.h"

struct Block;
class MainRenderer;
class Camera;

class World
{
public:
	World(const Camera& camera);
	~World();

	void setBlock(int x, int y, int z, Block block);
	Block getBlock(int x, int y, int z);

	void update(const Camera& camera);
	void updateChunk(int x, int y, int z);

	void render(MainRenderer& renderer, const Camera& camera);

	ChunkProvider& getChunkProvider();

private:
	void loadChunks(const Camera& camera);
	void updateChunks();

	ChunkProvider mChunkProvider;

	std::atomic<bool> mRunning{ true };
	std::vector<std::thread> mChunkThreads;

	std::mutex mMainMutex;
};

