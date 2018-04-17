#pragma once

#include <vector>
#include <ctime>
#include <random>


#include "WallBlock.h"


class Wall
{
public:
	Wall();
	~Wall();

private:
	std::vector<WallBlock> m_wallBlocks;
	int m_wallSize;
};

