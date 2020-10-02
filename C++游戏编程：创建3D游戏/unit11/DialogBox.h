#pragma once
#include "UIScreen.h"

class DialogBox :
    public UIScreen
{
public:
	//  较低的绘图顺序与较后的顺序相对应
	DialogBox(class Game* game, const std::string& text, std::function<void()> onOK);
	~DialogBox();
};

