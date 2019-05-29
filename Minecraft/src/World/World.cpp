#include <iostream>

#include "World.h"
#include "../Camera.h"

World::World(const Camera& camera) : m_chunkProvider(*this)
{
	for (int i = 0; i < 2; i++)
	{
		m_chunkThreads.emplace_back([&]()
			{
				LoadChunks(camera);
			});
	}
}

World::~World()
{
	m_running = false;
	for (auto& thread : m_chunkThreads)
	{
		thread.join();
	}
}

ChunkProvider& World::GetChunkProvider()
{
	return m_chunkProvider;
}

void World::LoadChunks(const Camera& camera)
{
	while (m_running)
	{
		auto pos = camera.position;

		m_chunkProvider.LoadChunk(pos.x, pos.z);
		std::cout << "Loaded chunk" << std::endl;
		//m_chunkProvider.GetChunk(pos.x, pos.z)
	}
}
