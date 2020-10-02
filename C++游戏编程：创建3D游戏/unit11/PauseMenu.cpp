#include "PauseMenu.h"
#include "Game.h"
#include "DialogBox.h"
#include <SDL.h>

PauseMenu::PauseMenu(Game* game)
	: UIScreen(game)
{
	//  游戏暂停
	mGame->SetState(Game::EPaused);
	//  禁用鼠标相对模式
	SetRelativeMouseMode(false);
	//  设置标题
	SetTitle("PauseTitle");
	//  添加恢复按钮
	AddButton("ResumeButton", [this]() {
		Close();
		});
	//  添加结束按钮
	AddButton("QuitButton", [this]() {
		new DialogBox(mGame, "QuitText",
			[this]() {
				mGame->SetState(Game::EQuit);
			});
		});
}

PauseMenu::~PauseMenu()
{
	//  启用鼠标相对模式
	SetRelativeMouseMode(true);
	//  返回游戏
	mGame->SetState(Game::EGameplay);
}

void PauseMenu::HandleKeyPress(int key)
{
	UIScreen::HandleKeyPress(key);
	//  按空格键关闭
	if (key == SDLK_ESCAPE)
	{
		Close();
	}
}