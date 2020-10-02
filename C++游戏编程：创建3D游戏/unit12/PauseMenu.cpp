#include "PauseMenu.h"
#include "Game.h"
#include "DialogBox.h"
#include <SDL.h>

PauseMenu::PauseMenu(Game* game)
	: UIScreen(game)
{
	//  ��Ϸ��ͣ
	mGame->SetState(Game::EPaused);
	//  ����������ģʽ
	SetRelativeMouseMode(false);
	//  ���ñ���
	SetTitle("PauseTitle");
	//  ��ӻָ���ť
	AddButton("ResumeButton", [this]() {
		Close();
		});
	//  ��ӽ�����ť
	AddButton("QuitButton", [this]() {
		new DialogBox(mGame, "QuitText",
			[this]() {
				mGame->SetState(Game::EQuit);
			});
		});
}

PauseMenu::~PauseMenu()
{
	//  ����������ģʽ
	SetRelativeMouseMode(true);
	//  ������Ϸ
	mGame->SetState(Game::EGameplay);
}

void PauseMenu::HandleKeyPress(int key)
{
	UIScreen::HandleKeyPress(key);
	//  ���ո���ر�
	if (key == SDLK_ESCAPE)
	{
		Close();
	}
}