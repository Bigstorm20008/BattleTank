#pragma once

#include "InputComponent.h"
#include "PlayerTank.h"

class PlayerTankInputComponent :
	public InputComponent
{
public:
	PlayerTankInputComponent();
	virtual ~PlayerTankInputComponent();
	void update(GameObject* gameObject) override;
};

