#pragma once

//forward declaration
class PlayerTank;
#include  "PlayerTank.h"

class InputComponent
{
public:
	InputComponent();
	virtual ~InputComponent();
	void update(PlayerTank& playerTank);
};

