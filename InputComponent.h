#pragma once

class GameObject;
#include "GameObject.h"


class InputComponent
{
public:
	InputComponent();
	virtual ~InputComponent();
	virtual void update(GameObject* gameObject) = 0;
};

