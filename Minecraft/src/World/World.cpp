#include <iostream>
#include <future>

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include "World.h"
#include "../Renderer/MainRenderer.h"
#include "../Camera.h"

std::thread chunkThread;
World::World(const Camera& camera) : m_chunkProvider(*this)
{
	for (int i = 0; i < 2; i++)
	{
		m_chunkThreads.emplace_back([&]()
			{
				LoadChunks(camera);
			});
	}

	//m_TestThread = std::thread([&]() { LoadChunks(camera); });
}

World::~World()
{
	m_running = false;
	for (auto& thread : m_chunkThreads)
	{
		thread.join();
	}
}

Block World::GetBlock(int x, int y, int z)
{
	return Block();
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

		if (minX > location.x ||
			minZ > location.y ||
			maxZ < location.y ||
			maxX < location.x)
		{
			iterator = chunks.erase(iterator);
			continue;
		}
		else
		{
			chunk.Render(renderer, camera);
			iterator++;
		}
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

			//int minX = std::max(cameraX - i, 0);
			//int minZ = std::max(cameraZ - i, 0);
			int minX = cameraX - i;
			int minZ = cameraZ - i;
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
