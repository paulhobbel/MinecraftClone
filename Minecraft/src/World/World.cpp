#include "World.h"

World::World() : m_chunkProvider(*this)
{

}

ChuckProvider& World::GetChunkProvider()
{
	return m_chunkProvider;
}
