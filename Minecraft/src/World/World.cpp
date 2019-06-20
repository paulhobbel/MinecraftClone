#include <iostream>
#include <future>

#include <glm/ext.hpp>

#include "World.h"
#include "../Camera.h"

#include "../Util/PositionUtil.h"
#include "../Constants.h"
#include "../Renderer/MainRenderer.h"

World::World(const Camera& camera) : mChunkProvider(*this)
{
	std::cout << "[INFO/World] Loading world..." << std::endl;
	for (int i = 0; i < 2; i++)
	{
		mChunkThreads.emplace_back([&]()
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				std::cout << "[DEBUG/World/Loader_Thread] Started async chunk loader." << std::endl;
				loadChunks(camera);
			});
	}
}

World::~World()
{
	std::cout << "[INFO/World] Shutting down current world, waiting for " << mChunkThreads.size() << " threads to close..." << std::endl;
	mRunning = false;
	for (auto& thread : mChunkThreads)
	{
		thread.join();
	}
}

void World::setBlock(int x, int y, int z, Block block)
{
	auto chunkPos = PositionUtil::worldToChunkPosition(x, y, z);
	auto blockPos = PositionUtil::worldToBlockPosition(x, y, z);

	mChunkProvider.getChunk(chunkPos.x, chunkPos.z).setBlock(blockPos.x, blockPos.y, blockPos.z, block);
}

Block World::getBlock(int x, int y, int z)
{
	auto chunkPos = PositionUtil::worldToChunkPosition(x, y, z);
	auto blockPos = PositionUtil::worldToBlockPosition(x, y, z);

	return mChunkProvider.getChunk(chunkPos.x, chunkPos.z).getBlock(blockPos.x, blockPos.y, blockPos.z);
}

void World::update(const Camera& camera)
{
	for(auto& event : mEvents)
	{
		event->handle(*this);
	}

	mEvents.clear();

	updateChunks();
}

void World::updateChunk(int blockX, int blockY, int blockZ)
{
	std::unique_lock<std::mutex> lock(mMainMutex);

	auto addChunkToUpdateBatch = [&](const glm::ivec3& key, std::shared_ptr<ChunkSection> section)
	{
		mChunkUpdates.emplace(key, section);
	};

	auto chunkPosition = PositionUtil::worldToChunkPosition(blockX, blockY, blockZ);
	auto chunkSectionY = blockY / CHUNK_SIZE;

	glm::ivec3 key(chunkPosition.x, chunkSectionY, chunkPosition.z);
	addChunkToUpdateBatch(key, mChunkProvider.getChunk(chunkPosition.x, chunkPosition.z).getSection(chunkSectionY));
	//mChunkUpdates.emplace(key, mChunkProvider.getChunk(chunkPosition.x, chunkPosition.z).getSection(chunkSectionY));

	auto sectionBlockXZ = PositionUtil::worldToBlockPosition(blockX, blockY, blockZ);
	auto sectionBlockY = blockY % CHUNK_SIZE;

	if (sectionBlockXZ.x == 0)
	{
		glm::ivec3 newKey(chunkPosition.x - 1, chunkSectionY, chunkPosition.z);
		addChunkToUpdateBatch(newKey, mChunkProvider.getChunk(newKey.x, newKey.z).getSection(newKey.y));
	}
	else if (sectionBlockXZ.x == CHUNK_SIZE - 1)
	{
		glm::ivec3 newKey(chunkPosition.x + 1, chunkSectionY, chunkPosition.z);
		addChunkToUpdateBatch(newKey, mChunkProvider.getChunk(newKey.x, newKey.z).getSection(newKey.y));
	}

	if (sectionBlockY == 0)
	{
		glm::ivec3 newKey(chunkPosition.x, chunkSectionY - 1, chunkPosition.z);
		addChunkToUpdateBatch(newKey, mChunkProvider.getChunk(newKey.x, newKey.z).getSection(newKey.y));
	}
	else if (sectionBlockY == CHUNK_SIZE - 1)
	{
		glm::ivec3 newKey(chunkPosition.x, chunkSectionY + 1, chunkPosition.z);
		addChunkToUpdateBatch(newKey, mChunkProvider.getChunk(newKey.x, newKey.z).getSection(newKey.y));
	}

	if (sectionBlockXZ.z == 0)
	{
		glm::ivec3 newKey(chunkPosition.x, chunkSectionY, chunkPosition.z - 1);
		addChunkToUpdateBatch(newKey, mChunkProvider.getChunk(newKey.x, newKey.z).getSection(newKey.y));
	}
	else if (sectionBlockXZ.z == CHUNK_SIZE - 1)
	{
		glm::ivec3 newKey(chunkPosition.x, chunkSectionY, chunkPosition.z + 1);
		addChunkToUpdateBatch(newKey, mChunkProvider.getChunk(newKey.x, newKey.z).getSection(newKey.y));
	}
}

void World::render(MainRenderer& renderer, const Camera& camera)
{
	std::unique_lock<std::mutex> lock(mMainMutex);

	auto& chunks = mChunkProvider.getChunks();
	for (auto iterator = chunks.begin(); iterator != chunks.end(); ++iterator)
	{
		auto chunk = iterator->second;
		//std::cout << "[DEBUG/World] Rendering chunk:" << glm::to_string(chunk.GetPosition()) << std::endl;

		int cameraX = camera.position.x;
		int cameraZ = camera.position.z;

		int minX = (cameraX / CHUNK_SIZE) - 12;
		int minZ = (cameraZ / CHUNK_SIZE) - 12;
		int maxX = (cameraX / CHUNK_SIZE) + 12;
		int maxZ = (cameraZ / CHUNK_SIZE) + 12;

		auto location = chunk->getPosition();

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
		chunk->render(renderer, camera);
		//}
		//renderer.RenderChunk(chunk);
	}
}

ChunkProvider& World::getChunkProvider()
{
	return mChunkProvider;
}

int loadDistance = 2;
void World::loadChunks(const Camera& camera)
{
	while (mRunning)
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
					std::unique_lock<std::mutex> lock(mMainMutex);
					isMeshMade = mChunkProvider.makeMesh(x, z, camera);

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

		if (loadDistance > 5)
			loadDistance = 2;
	}
}

void World::updateChunks()
{
	std::unique_lock<std::mutex> lock(mMainMutex);
	for (auto& c : mChunkUpdates)
	{
		auto s = c.second;
		s->makeMesh();
		s->getMesh()->setHasBuffered(false);
	}
	mChunkUpdates.clear();
}
