#include <iostream>
#include <future>

#include <glm/vec3.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include "World.h"
#include "../Renderer/MainRenderer.h"
#include "../Camera.h"

#include "../Util/PositionUtilities.h"

std::thread chunkThread;
World::World(const Camera& camera) : m_chunkProvider(*this)
{
	std::cout << "[INFO/World] Loading world..." << std::endl;
	for (int i = 0; i < 2; i++)
	{
		m_chunkThreads.emplace_back([&]()
			{
				std::cout << "[DEBUG/World/Loader_Thread] Started async chunk loader." << std::endl;
				LoadChunks(camera);
			});
	}
}

World::~World()
{
	std::cout << "[INFO/World] Shutting down current world, waiting for " << m_chunkThreads.size() << " threads to close..." << std::endl;
	m_running = false;
	for (auto& thread : m_chunkThreads)
	{
		thread.join();
	}
}

void World::SetBlock(int x, int y, int z, Block block)
{
	auto chunkPos = PositionUtilities::WorldToChunkPosition(x, y, z);
	auto blockPos = PositionUtilities::WorldToBlockPosition(x, y, z);

	m_chunkProvider.GetChunk(chunkPos.x, chunkPos.z).SetBlock(blockPos.x, blockPos.y, blockPos.z, block);
}

Block World::GetBlock(int x, int y, int z)
{
	auto chunkPos = PositionUtilities::WorldToChunkPosition(x, y, z);
	auto blockPos = PositionUtilities::WorldToBlockPosition(x, y, z);

	return m_chunkProvider.GetChunk(chunkPos.x, chunkPos.z).GetBlock(blockPos.x, blockPos.y, blockPos.z);
}

void World::Render(MainRenderer& renderer, const Camera& camera)
{
	std::unique_lock<std::mutex> lock(m_mainMutex);

	auto& chunks = m_chunkProvider.GetChunks();
	for (auto iterator = chunks.begin(); iterator != chunks.end();)
	{
		Chunk& chunk = iterator->second;
		//std::cout << "[DEBUG/World] Rendering chunk:" << glm::to_string(chunk.GetPosition()) << std::endl;

		int cameraX = camera.position.x;
		int cameraZ = camera.position.z;

		int minX = (cameraX / CHUNK_SIZE) - 12;
		int minZ = (cameraZ / CHUNK_SIZE) - 12;
		int maxX = (cameraX / CHUNK_SIZE) + 12;
		int maxZ = (cameraZ / CHUNK_SIZE) + 12;

		auto location = chunk.GetPosition();

		/*if (minX > location.x ||
			minZ > location.y ||
			maxZ < location.y ||
			maxX < location.x)
		{
			iterator = chunks.erase(iterator);
			continue;
		}*/
		//else
		//{
			chunk.Render(renderer, camera);
			iterator++;
		//}
		//renderer.RenderChunk(chunk);
	}
}

ChunkProvider& World::GetChunkProvider()
{
	return m_chunkProvider;
}

int loadDistance = 2;
void World::LoadChunks(const Camera& camera)
{
	while (m_running)
	{
		bool isMeshMade = false;
		int cameraX = static_cast<int>(camera.position.x) / CHUNK_SIZE;
		int cameraZ = static_cast<int>(camera.position.z) / CHUNK_SIZE;

		for (int i = 0; i <= loadDistance; i++)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			// TODO: ChunkProvider - Fix minus coordinates
			int minX = std::max(cameraX - i, 0);
			int minZ = std::max(cameraZ - i, 0);
			//int minX = cameraX - i;
			//int minZ = cameraZ - i;
			int maxX = cameraX + i;
			int maxZ = cameraZ + i;

			for (int x = minX; x < maxX; ++x)
			{
				for (int z = minZ; z < maxZ; ++z)
				{
					std::unique_lock<std::mutex> lock(m_mainMutex);
					isMeshMade = m_chunkProvider.MakeMesh(x, z, camera);

					//if (isMeshMade)
					//	break;
				}

				//if (isMeshMade)
				//	break;
			}

			if (isMeshMade)
				break;
		}

		if (!isMeshMade)
			loadDistance++;

		if (loadDistance > 12)
			loadDistance = 2;
	}
}
