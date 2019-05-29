#include "World.h"

World::World() : m_chunkProvider(*this)
{

}

ChunkProvider& World::GetChunkProvider()
{
	return m_chunkProvider;
}
