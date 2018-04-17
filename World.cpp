#include "World.h"


World::World(int width,int height)
{
	m_width = width;
	m_height = height;
}


World::~World()
{
}

int World::getWidth() const
{
	return m_width;
}

int World::getHeight() const
{
	return m_height;
}
