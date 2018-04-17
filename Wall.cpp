#include "Wall.h"


Wall::Wall()
{
	std::default_random_engine randomeEngine(static_cast<unsigned int>(time(0)));
	std::uniform_int_distribution<int> wallBlocksCount(1, 15);
	m_wallSize = wallBlocksCount(randomeEngine);

	m_wallBlocks.reserve(m_wallSize);
}


Wall::~Wall()
{
}
