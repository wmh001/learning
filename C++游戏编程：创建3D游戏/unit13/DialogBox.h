#pragma once
#include "UIScreen.h"

class DialogBox :
    public UIScreen
{
public:
	//  �ϵ͵Ļ�ͼ˳����Ϻ��˳�����Ӧ
	DialogBox(class Game* game, const std::string& text, std::function<void()> onOK);
	~DialogBox();
};

