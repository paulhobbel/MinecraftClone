#pragma once

#include <atomic>
#include <thread>
#include <mutex>
#include <vector>

#include "Chunk/ChunkProvider.h"
#include "Event/IWorldEvent.h"

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

	template<typename T, typename... Args>
	void addEvent(Args&& ... args)
	{
		mEvents.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}

private:
	void loadChunks(const Camera& camera);
	void updateChunks();

	std::vector<std::unique_ptr<IWorldEvent>> mEvents;
	std::unordered_map<glm::ivec3, std::shared_ptr<ChunkSection>> mChunkUpdates;

	ChunkProvider mChunkProvider;

	std::atomic<bool> mRunning{ true };
	std::vector<std::thread> mChunkThreads;

	std::mutex mMainMutex;
};

