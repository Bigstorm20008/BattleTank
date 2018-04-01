#pragma once

//forward declaration
class InputComponent;
class GraficsComponent;

#include "InputComponent.h"
#include "GraficsComponent.h"

class PlayerTank
{
public:
	PlayerTank();
	virtual ~PlayerTank();
private:
	InputComponent* m_inputComponent;
	GraficsComponent* m_graficsComponent;
};

