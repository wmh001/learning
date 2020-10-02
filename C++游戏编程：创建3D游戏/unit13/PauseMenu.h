#pragma once
#include "UIScreen.h"

class PauseMenu :
    public UIScreen
{
public:
	PauseMenu(class Game* game);
	~PauseMenu();
	//   Û±Í ‰»Î
	void HandleKeyPress(int key) override;
};

