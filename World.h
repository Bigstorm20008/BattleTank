#pragma once

#include <vector>


#include "GameObject.h"


class World
{
public:
	World(int width,int height);
	~World();

	int getWidth() const;
	int getHeight() const;
private:
	int m_width;
	int m_height;

	std::vector<GameObject*> m_gameObjects;

};

