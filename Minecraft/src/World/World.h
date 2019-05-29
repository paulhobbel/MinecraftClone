#pragma once

#include <atomic>
#include <thread>
#include <mutex>
#include <vector>

#include "Chunk/ChunkProvider.h"

struct Block;
class Camera;

class World
{
public:
	World(const Camera& camera);
	~World();

	void SetBlock(int x, int y, int z, Block block);
	Block GetBlock(int x, int y, int z);

	void Update(const Camera& camera);
	void UpdateChunk(int x, int y, int z);

	ChunkProvider& GetChunkProvider();

private:
	void LoadChunks(const Camera& camera);
	void UpdateChunks();

	ChunkProvider m_chunkProvider;

	std::atomic<bool> m_running{ true };
	std::vector<std::thread> m_chunkThreads;
	
	std::mutex m_mainMutex;
	std::mutex m_geneMutex;
};

